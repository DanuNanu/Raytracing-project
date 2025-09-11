#ifndef CUBE_H
#define CUBE_H

#include "hittable.h"
#include "vec3.h"
#include <limits>
#include "interval.h"

 double do_calc_max (double min, double max, double origin, double direction) {
        return std::fmax((min-origin)/direction, (max-origin)/direction);
    }

    double do_calc_min (double min, double max, double origin, double direction) {
        return std::fmin((min-origin)/direction, (max-origin)/direction);
    }

    

class cube : public hittable {
    private:
    coord3 center;
    double s_length;
    const double infinity = std::numeric_limits<double>::infinity();

    public:
    cube (const coord3& center, double s_length) : center(center), s_length(std::fmax(0, s_length)) {}


    bool hit (const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 dir = r.direction();
            coord3 origin = r.origin();
            double half = s_length/2.0;
            double x_min = center.x() - half;
            double x_max = center.x() +half;
            double y_min = center.y() - half;
            double y_max = center.y() + half;
            double z_min = center.z() - half;
            double z_max = center.z() + half;
            double txmax = 0.0;
            double txmin = 0.0;
            double tymax = 0.0;
            double tymin = 0.0;
            double tzmax = 0.0;
            double tzmin = 0.0;
            if (std::abs(r.direction().x()) < 1e-12) {
                if (origin.x() < x_min || origin.x()> x_max) {
                    return false;
                } else {txmin = -infinity; txmax = infinity;}
            }
            if (std::abs(r.direction().y()) <  1e-12) {
                if (origin.y() < y_min || origin.y()> y_max) {
                    return false;
                } else {tymin = -infinity; tymax = infinity;}
            }
            if (std::abs(r.direction().z()) <  1e-12) {
                if (origin.z() < z_min || origin.z()> z_max) {
                    return false;
                } else {tzmin = -infinity; tzmax = infinity;}
            }

                txmin = (txmin == 0.0) ? do_calc_min(x_min, x_max, r.origin().x(), r.direction().x()): txmin;
                txmax = (txmax == 0.0) ? do_calc_max(x_min, x_max, r.origin().x(), r.direction().x()): txmax;
                tymin = (tymin == 0.0) ? do_calc_min(y_min, y_max, r.origin().y(), r.direction().y()): tymin;
                tymax = (tymax == 0.0) ? do_calc_max(y_min, y_max, r.origin().y(), r.direction().y()): tymax;
                tzmin = (tzmin == 0.0) ? do_calc_min(z_min, z_max, r.origin().z(), r.direction().z()): tzmin;
                tzmax = (tzmax == 0.0) ? do_calc_max(z_min, z_max, r.origin().z(), r.direction().z()): tzmax;
                double t_inter = std::fmax(txmin,tymin);
                double t_enter = std::fmax(t_inter, tzmin);
                double t_inter2 = std::fmin(txmax, tymax);
                double texit = std::fmin(t_inter2, tzmax);
                double t0 = std::fmax(t_enter, ray_t.min);
                double t1 = std::fmin(texit, ray_t.max);
                if (t0 > t1) {
                    return false;
                } else {
                    vec3 outward_normal = vec3(-1,0,0);
                     coord3 ray = origin + t_enter*dir;
                    double dx_min = abs(ray.x() - x_min);
                    double dx_max = abs(x_max - ray.x());
                    double dy_min = abs(ray.y() - y_min);
                    double dy_max = abs(y_max - ray.y());
                    double dz_min = abs(ray.z() - z_min);
                    double dz_max = abs(z_max - ray.z());

                    double d = dx_min;

                    if (dx_max < d) { d = dx_max; outward_normal = vec3(+1,0,0); }
                    if (dy_min < d) { d = dy_min; outward_normal = vec3(0,-1,0); }
                    if (dy_max < d) { d = dy_max; outward_normal = vec3(0,+1,0); }
                    if (dz_min < d) { d = dz_min; outward_normal = vec3(0,0,-1); }
                    if (dz_max < d) {  outward_normal = vec3(0,0,+1); }
                    rec.t = t_enter;
                    rec.p = r.at(rec.t);
                    rec.set_face_normal(r, outward_normal);
                    return true;
             }

                }

                
            };



#endif 
