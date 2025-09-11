#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    private:
    coord3 org;
    vec3 dir;

    public:
    ray() {};

    ray(const coord3& origin, const vec3& direction) : org(origin), dir(direction) {}

    const coord3& origin() const {return org;}
    const vec3& direction() const {return dir;}

    coord3 at(double t) const {
        return org + t*dir;
    }
};

#endif