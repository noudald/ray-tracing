#include <iostream>
#include <memory>

#include <color.h>
#include <ray.h>
#include <vec3.h>
#include <hittable.h>
#include <hittable_list.h>
#include <utils.h>
#include <sphere.h>


Color ray_color(const Ray &r, const Hittable &world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + Color(1.0, 1.0, 1.0));
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

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0.0, 0.0, 0.0);
    auto horizontal = Vec3(viewport_width, 0.0, 0.0);
    auto vertical = Vec3(0.0, viewport_height, 0.0);
    auto lower_left_corner = origin
        - 0.5 * horizontal
        - 0.5 * vertical
        - Vec3(0.0, 0.0, focal_length);

    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));

    // Render Image.
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--) {
        std::cerr << ".";
        for (int i = 0; i < image_width; i++) {
            auto u = float(i) / (image_width - 1);
            auto v = float(j) / (image_height - 1);

            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            auto pixel_color = ray_color(r, world);

            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << std::endl;
}
