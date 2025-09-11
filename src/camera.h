#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "colour.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"

class camera {
    private:
    int image_height;
    coord3 camera_center;
    coord3 zero_pixel;
    vec3 delta_u;
    vec3 delta_v;

    void initialise() {
        int image_height = int(image_width/aspect_ratio);
         image_height = (image_height < 1) ? 1: image_height;
         camera_center = coord3(0,0,0);
         auto focal_length = 1.0;
         auto viewport_height = 2.0;
         auto viewport_width = viewport_height * (double(image_width)/image_height);


         auto Vu = vec3(viewport_width,0 ,0);
         auto Vv = vec3(0, -viewport_height, 0);

         delta_u = Vu/image_width;
         delta_v = Vv/image_height;

         auto v_upper_left = camera_center - vec3(0,0,focal_length) - Vu/2 - Vv/2;
         zero_pixel = v_upper_left + 0.5*(delta_u + delta_v);
    }

    colour ray_colour(const ray& r, const hittable& world) {
        hit_record rec;
        if (world.hit(r,interval(0, infinity), rec)) {
            return 0.5* (rec.normal + colour(1,1,1));
        }

        vec3 unit_direction = unit_vec(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*colour(1.0,1.0,1.0) + a*colour(0.5,0.7,0.5);
    }


    public:
    double aspect_ratio = 16.0/10.0;
    int image_width = 800;

    void render(const hittable& world) {
        initialise();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; i++) {
        // Image rendering progress indicator
        std::clog <<"\rRendered : " << i << "% " << ' ' << std::flush;
        // inner loop looks at the column within that row
        for (int j = 0; j < image_width; j++) {
            auto pixel_center = zero_pixel + (j*delta_u) + (i * delta_v);
            auto ray_dir = pixel_center - camera_center;
            ray rprime(camera_center, ray_dir);

            colour pxl_clr = ray_colour(rprime, world);
            write_colour(std::cout, pxl_clr);
        }
    }
      std::clog << "\rFinished.      \n";
}


    };

#endif