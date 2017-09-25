#include <nana/gui.hpp>
#include "plot.h"

int main()
{

    using namespace nana;

    try
    {
        form fm;

        // construct plot to be drawn on form
        plot::plot thePlot( fm );

        // construct first plot trace
        plot::trace t1;

        // provide some data to trace
        std::vector< double > d1 { 10, 15, 20, 25, 30, 25, 20, 15, 10 };
        t1.add( d1 );

        // plot in blue
        t1.color( colors::blue );

        // add to plot
        thePlot.add( t1 );

        // construct second trace
        plot::trace t2;

        // provide data
        std::vector< double > d2 { 20, 30, 40, 50, 60, 50, 40, 30, 20 };
        t2.add( d2 );

        // plot in red
        t2.color( colors::red );

        // add to plot
        thePlot.add( t2 );

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

