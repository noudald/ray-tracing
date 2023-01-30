#include <iostream>
#include <memory>

#include <color.h>
#include <ray.h>
#include <vec3.h>
#include <hittable.h>
#include <hittable_list.h>
#include <utils.h>
#include <sphere.h>
#include <camera.h>


Color ray_color(const Ray &r, const Hittable &world, int depth=50) {
    hit_record rec;

    if (depth <= 0) {
        return Color(0.0, 0.0, 0.0);
    }

    if (world.hit(r, 0.001, infinity, rec)) {
        Point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth-1);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction[1] + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


int main() {
    // Image settings.
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;

    // Camera
    Camera camera;

    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));

    // Render Image.
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--) {
        if (j % (image_height / 10) == 0) {
            std::cerr << ".";
        }
        for (int i = 0; i < image_width; i++) {
            Color pixel_color(0.0, 0.0, 0.0);
            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = (float(i) + random_float()) / (image_width - 1);
                auto v = (float(j) + random_float()) / (image_height - 1);

                auto r = camera.getRay(u, v);
                pixel_color += ray_color(r, world);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << std::endl;
}
