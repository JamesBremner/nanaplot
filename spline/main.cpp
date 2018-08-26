#include <iostream>
#include <nana/gui.hpp>
#include "../plot.h"

// spline calculation code interface
// from https://github.com/JamesBremner/raven-cSpline
#include "cSpline.h"

int main()
{

    using namespace nana;

    try
    {
        form fm;
        fm.caption("Spline Curve");

        // construct plot to be drawn on form
        plot::plot thePlot( fm );

        // spline input
        std::vector< double > x { 0, 1, 2, 3, 4 };
        std::vector< double > y {  100, 50, -100, 50, 200 };

        // construct spline curve through input points
        raven::cSpline spline( x, y );
        std::vector< double > curve;
        for( double x = 0; x < 4; x += 0.1) {
            curve.push_back( spline.getY( x ));
        }

        // construct plot trace
        plot::trace& t1 = thePlot.AddStaticTrace();
        t1.set( curve );
        t1.color( colors::red );

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

