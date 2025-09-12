#include "common.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "cube.h"

int main() {
    hittable_list world;

   world.add(make_shared<sphere>(coord3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(coord3(0,-100.5,-1), 100));
    world.add(make_shared<cube>(coord3(-0.25,0.5,-1), 0.7));

    camera cam;
    cam.aspect_ratio = 16.0/10.0;
    cam.image_width = 800;
    cam.samples_per_pixel= 100;
    cam.render(world);
}