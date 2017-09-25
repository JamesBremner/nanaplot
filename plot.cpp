#include <nana/gui.hpp>
#include "plot.h"
namespace nana
{
namespace plot
{

plot::plot( window parent )
    : myParent( parent )
{
    // arrange for the plot to be updated when needed
    myDrawing = new drawing( parent );
    myDrawing->draw([this](paint::graphics& graph)
    {
        // calculate scaling factors
        // so plot will fit
        CalcScale(
            graph.width(),
            graph.height() );

        myAxis->update( graph );

        // draw all the traces
        for( auto t : myTrace )
            t->update( graph );
    });

    myAxis = new axis( this );
}

void plot::CalcScale( int w, int h )
{
    int maxCount = 0;
    myTrace[0]->bounds( myMinY, myMaxY );
    for( auto& t : myTrace )
    {
        if( t->size() > maxCount )
            maxCount = t->size();
        int min, max;
        t->bounds( min, max );
        if( min < myMinY )
            myMinY = min;
        if( max > myMaxY )
            myMaxY = max;
    }

    myXinc = w / maxCount;
    if( myMaxY == myMinY )
        myScale = 1;
    else
    myScale = h / ( myMaxY - myMinY );
    myYOffset = h + myScale * myMinY;
}
void trace::add( const std::vector< double >& y )
{
    if( myfRealTime )
        throw std::runtime_error("nanaplot error: static data added to realtime trace");
    myY = y;
}
void trace::add( double y )
{
    if( ! myfRealTime )
        throw std::runtime_error("nanaplot error: realtime data added to no realtime trace");
    myY[ myRealTimeNext++ ] = y;
    if( myRealTimeNext >= (int)myY.size() )
        myRealTimeNext = 0;

    myPlot->update();
}

void trace::bounds( int& min, int& max )
{
    min = myY[0];
    max = min;
    for( auto y : myY )
    {
        if( y < min )
            min = y;
        if( y > max )
            max = y;
    }
    min--;
    max++;
}

void trace::update( paint::graphics& graph )
{
    bool first = true;
    int x = 0;
    int xinc = myPlot->xinc();
    double s = myPlot->Scale();
    int yOffset = myPlot->YOffset();
    double prev;

    // loop over data points

    if( ! myfRealTime )
    {
        for( auto y : myY )
        {
            if( first )
            {
                first = false;
                prev = y;
                continue;
            }
            // draw line from previous to this data point
            graph.line(
                point(x, yOffset - prev * s),
                point(x+xinc, yOffset - y * s),
                myColor);

            x += xinc;
            prev = y;
        }
    }
    else
    {
        int yidx = myRealTimeNext;
        do
        {
            double y = myY[ yidx ];
            yidx++;
            if( yidx >= (int)myY.size() )
                yidx = 0;

            if( first )
            {
                first = false;
                prev = y;
                continue;
            }
            // draw line from previous to this data point
            graph.line(
                point(x, yOffset - prev * s),
                point(x+xinc, yOffset - y * s),
                myColor);

            x += xinc;
            prev = y;

        }
        while( yidx != myRealTimeNext );
    }
}

axis::axis( plot * p )
    : myPlot( p )
{
    myLabelMin = new label( myPlot->parent(),  rectangle{ 10, 10, 50, 50 } );
    myLabelMin->caption("test");
    myLabelMax = new label( myPlot->parent(),  rectangle{ 10, 10, 50, 50 } );
    myLabelMax->caption("test");
}

void axis::update( paint::graphics& graph )
{
    myLabelMin->move( 5,graph.height()-20 );
    std::stringstream ss;
    ss << myPlot->minY();
    myLabelMin->caption(ss.str());
    ss.str("");
    ss << myPlot->maxY();
    myLabelMax->caption(ss.str());
}


}
}
