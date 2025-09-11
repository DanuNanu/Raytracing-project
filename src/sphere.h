#ifndef SPHERE_H
#define SPHERE_H


#include "hittable.h"
#include "vec3.h"
#include "interval.h"

class sphere : public hittable {
    private:
    coord3 center;
    double radius;


    public: 
    sphere (const coord3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit (const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = center - r.origin();
        auto a = r.direction().norm_sqrd();
        auto b = dot(r.direction(), oc);
        auto c = oc.norm_sqrd() - (radius*radius);
        auto discm = b*b- a*c;
        if (discm < 0) {
            return false;
        } 

        auto root = (b - std::sqrt(discm))/a;
        if (!ray_t.sorrounds(root)) {
            root = (b + std::sqrt(discm))/a;
            if (!ray_t.sorrounds(root)) {
                return false;
            }
        }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) /radius;
            rec.set_face_normal(r, outward_normal);
            return true;
    }

};


#endif