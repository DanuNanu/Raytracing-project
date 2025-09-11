#include "vec3.h"
#include "colour.h"
#include "ray.h"
#include <iostream>


double hit_sphere(const coord3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0*dot(r.direction(), oc);
    auto c = dot(oc, oc) - (radius*radius);
    auto discm = (b*b) - 4*a*c;
    if (discm < 0) {
        return -1.0;
    } else {
        return (-b -std::sqrt(discm))/(2.0*a);
    }
}

colour ray_colour(const ray& r) {
        auto t = hit_sphere(coord3(0,0,-1),0.5,r);
        if (t > 0.0) {
            vec3 normal = unit_vec(r.at(t)-vec3(0,0,-1));
            return 0.5*colour(normal.x()+1, normal.y()+1, normal.z()+1);
        }
        

        vec3 unit_direction = unit_vec(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*colour(1.0,1.0,1.0) + a*colour(0.5,0.7,1.0);
    }


int main() {
    auto aspect_ratio = 16.0/10.0;
    int image_width = 400;
    
    int image_height = int(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1: image_height;

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = coord3(0,0,0);

    auto Vu = vec3(viewport_width,0 ,0);
    auto Vv = vec3(0, -viewport_height, 0);

    auto delta_u = Vu/image_width;
    auto delta_v = Vv/image_height;

    auto v_upper_left = camera_center - vec3(0,0,focal_length) - Vu/2 - Vv/2;
    auto zero_pix = v_upper_left + 0.5*(delta_u + delta_v);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

 
//outer loop looks at the current row, starting at the top 
    for (int i = 0; i < image_height; i++) {
        // Image rendering progress indicator
        std::clog <<"\rRendered : " << i << "% " << ' ' << std::flush;
        // inner loop looks at the column within that row
        for (int j = 0; j < image_width; j++) {
            auto pixel_center = zero_pix + (j*delta_u) + (i * delta_v);
            auto ray_dir = pixel_center - camera_center;
            ray rprime(camera_center, ray_dir);
            colour pxl_clr = ray_colour(rprime);
            write_colour(std::cout, pxl_clr);
        }
    }
    std::clog << "\rFinished.      \n";
}