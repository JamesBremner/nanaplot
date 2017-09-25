#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>
#include "../plot.h"

int main()
{

    using namespace nana;

    try
    {
        form fm;

        // construct plot to be drawn on form
        plot::plot thePlot( fm );

        // construct plot trace
        // displaying 20 points before they scroll off the plot
        plot::trace& t1 = thePlot.AddRealTimeTrace( 20 );

        // plot in blue
        t1.color( colors::blue );

        // create timer to provide new data regularly
        timer theTimer;
        theTimer.interval( 300 );
        theTimer.elapse([ &t1 ]()
        {
            static std::vector< double > d1 { 10, 15, 20, 25, 30, 25, 20, 15, 10 };
            static int p = 0;
            t1.add( d1[ p++ ]);
            if( p == 8 )
                p = 0;
        });
        theTimer.start();

        // show and run
        fm.show();
        exec();
    }
    catch( std::runtime_error& e )
    {
        msgbox mb( e.what() );
        mb();
    }
}

