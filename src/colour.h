#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include "interval.h"
#include <iostream>

using colour = vec3;

inline double linear_to_gamma (double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }
    return 0.0;
}


void write_colour(std::ostream& out, const colour& pxl_clr) {
    auto r = pxl_clr.x();
    auto g = pxl_clr.y();
    auto b = pxl_clr.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.0000, 0.9999);
    int rint = int(256 * intensity.clamp(r));
    int gint = int(256 * intensity.clamp(g));
    int bint = int(255.999 * intensity.clamp(b));

    out << rint << ' ' << gint << ' ' << bint << '\n';
}

#endif