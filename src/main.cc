#include <iostream>


int main() {

    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

 
//outer loop looks at the current row, starting at the top 
    for (int i = 0; i < image_height; i++) {
        // Image rendering progress indicator
        std::clog <<"\rRendered : " << i << "% " << ' ' << std::flush;
        // inner loop looks at the column within that row
        for (int j = 0; j < image_width; j++) {
            // red value increases from 0-> 1 left to right
            auto r = 0.0;
            // green value increase 0 -> 1 up to down
            auto g = double(i) / (image_height - 1);
            auto b = double(j)/ (image_width -1);

            // converting rgb values to integer
            int ir = int(255.99 * r);
            int ig  = int(255.999 * g);
            int ib = int(255.999 * b);

            // pronting each pixed as three integer value
            // pixels are written out in rows 
            // for example 255 0 0 is a red pixel
            // each row represents a pixel
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\rFinished.      \n";
}