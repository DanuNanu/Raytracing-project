#ifndef MATERIAL_H
#define MATERIAL_H

#include "colour.h"
#include "hittable.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered
        ) const {
            return false;
        }
};

#endif