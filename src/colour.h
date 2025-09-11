#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include <iostream>

using colour = vec3;

void write_colour(std::ostream& out, const colour& pxl_clr) {
    auto r = pxl_clr.x();
    auto g = pxl_clr.y();
    auto b = pxl_clr.z();

    int rint = int(255.999 * r);
    int gint = int(255.999 * g);
    int bint = int(255.999 * b);

    out << rint << ' ' << gint << ' ' << bint << '\n';
}




#endif