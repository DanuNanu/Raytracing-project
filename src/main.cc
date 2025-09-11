#include "common.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "cube.h"

/* bool hit_cube(const coord3& center, double side_length, const ray& r, coord3& norma) {
    double half = side_length/2.0;
    double x_min = center.x() - half;
    double x_max = center.x() +half;
    double y_min = center.y() - half;
    double y_max = center.y() + half;
    double z_min = center.z() - half;
    double z_max = center.z() + half;
    double txmax = std::fmax((x_min-r.origin().x())/r.direction().x(), (x_max-r.origin().x())/r.direction().x());
    double txmin = std::fmin((x_min-r.origin().x())/r.direction().x(), (x_max-r.origin().x())/r.direction().x());
    double tymax = std::fmax((y_min-r.origin().y())/r.direction().y(), (y_max-r.origin().y())/r.direction().y());
    double tymin = std::fmin((y_min-r.origin().y())/r.direction().y(), (y_max-r.origin().y())/r.direction().y());
    double tzmax = std::fmax((z_min-r.origin().z())/r.direction().z(), (z_max-r.origin().z())/r.direction().z());
    double tzmin = std::fmin((z_min-r.origin().z())/r.direction().z(), (z_max-r.origin().z())/r.direction().z());
    double t_inter = std::fmax(txmin,tymin);
    double t_enter = std::fmax(t_inter, tzmin);
    double t_inter2 = std::fmin(txmax, tymax);
    double texit = std::fmin(t_inter2, tzmax);
    if (t_enter > texit || texit < 0.0) {
        return false;
    } else {
        coord3 ray = r.origin() + t_enter*r.direction();
        if (t_enter == txmin) {
            double dxpl = abs(x_max - ray.x());
            double dxmi = abs(ray.x() - x_min);
            norma = (dxpl < dxmi)? coord3(1,0,0) : coord3(-1,0,0);
        } else if (t_enter == tymin) {
            double dypl = abs(y_max - ray.y());
            double dymi = abs(ray.y() - y_min);
            norma = (dypl < dymi)? coord3(0,1,0) : coord3(0,-1,0);
        } else {
            double dzpl = abs(z_max - ray.z());
            double dzmi = abs(ray.z() - z_min);
            norma = (dzpl < dzmi)? coord3(0,0,1) : coord3(0,0,-1);
        }
        return true;
    }


} */

colour ray_colour(const ray& r, const hittable& world) {
        hit_record rec;
        if (world.hit(r,0,infinity, rec)) {
            return 0.5* (rec.normal + colour(1,1,1));
        }
        
       /*  coord3 norma = coord3(0.0,0.0,0.0);
        if (hit_cube(coord3(0,0,-1), 0.5, r, norma)) {
            return 0.5*colour(norma.x()+1, norma.y()+1, norma.z()+1);
        } */

        vec3 unit_direction = unit_vec(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*colour(1.0,1.0,1.0) + a*colour(0.5,0.7,0.5);
    }


int main() {
    auto aspect_ratio = 16.0/10.0;
    int image_width = 800;
    
    int image_height = int(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1: image_height;


    hittable_list world;
    world.add(make_shared<sphere>(coord3(-1,1,-1), 0.5));
   world.add(make_shared<sphere>(coord3(0,-100.5,-1), 100));
    world.add(make_shared<cube>(coord3(0,0,-1), 0.5));
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

            colour pxl_clr = ray_colour(rprime, world);
            write_colour(std::cout, pxl_clr);
        }
    }
    std::clog << "\rFinished.      \n";
}