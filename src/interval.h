#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

const double infini = std::numeric_limits<double>::infinity();

class interval {
    public:
    double min, max;

    interval() : min(+infini), max(-infini) {}

    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains (double x) const {
        return min <= x && x <= max;
    }

    bool sorrounds(double x) const {
        return min < x && x < max;
    }

    static const interval empty, universe;

};


const interval interval::empty    = interval(+infini, -infini);
const interval interval::universe = interval(-infini, +infini);

#endif