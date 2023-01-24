#include <iostream>

#include <vec3.h>

int main() {
    // Image settings.
    const int image_width = 256;
    const int image_height = 256;

    // Render Image.
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--) {
        std::cerr << ".";
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
    std::cerr << std::endl;

    Vec3 vec(1.0, 2.0, 3.0);
    std::cout << vec << " " << dot(vec, vec) << std::endl;
}
