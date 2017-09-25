#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

namespace nana
{
namespace plot
{
class plot;

/// Single trace to be plotted
class trace
{
public:

    /// set data
    void add( const std::vector< double >& y )
    {
        myY = y;
    }

    /// set color
    void color( const colors & clr )
    {
        myColor = clr;
    }

    /// set plot where this trace will appear
    void Plot( plot * p )
    {
        myPlot = p;
    }

    int size()
    {
        return (int) myY.size();
    }

    void bounds( int& min, int& max );

    /// draw
    void update( paint::graphics& graph );

private:
    plot * myPlot;
    std::vector< double > myY;
    colors myColor;
};

class axis
{
public:
    axis( plot * p );

    ~axis()
    {
        delete myLabelMin;
        delete myLabelMax;
    }

    /// draw
    void update( paint::graphics& graph );

private:
    plot * myPlot;
    label * myLabelMin;
    label * myLabelMax;
};


/** 2D plotting */
class plot
{
public:

    /** CTOR
        @param[in parent window where plot will be drawn
    */
    plot( window parent );

    ~plot()
    {
        delete myAxis;
    }

    /** Add a data trace
        @param[in] t the data trace to be added
    */
    void add( trace& t )
    {
        t.Plot( this );
        myTrace.push_back( t );
    }

    int xinc()
    {
        return myXinc;
    }
    int minY()
    {
        return myMinY;
    }
    int maxY()
    {
        return myMaxY;
    }
    double Scale()
    {
        return myScale;
    }
    int YOffset()
    {
        return myYOffset;
    }
    window parent()
    {
        return myParent;
    }

private:

    ///window where plot will be drawn
    window myParent;

    drawing * myDrawing;

    axis * myAxis;

    /// plot traces
    std::vector< trace > myTrace;

    int myXinc;
    int myMinY, myMaxY;
    double myScale;
    int myYOffset;

    /** calculate scaling factors so plot will fit in window client area
        @param[in] w width
        @param[in] h height
    */
    void CalcScale( int w, int h );

};

}
}
