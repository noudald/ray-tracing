#include <iostream>
#include <memory>

#include <camera.h>
#include <color.h>
#include <hittable.h>
#include <hittable_list.h>
#include <material.h>
#include <ray.h>
#include <sphere.h>
#include <utils.h>
#include <vec3.h>


Color ray_color(const Ray &r, const Hittable &world, int depth=50) {
    hit_record rec;

    if (depth <= 0) {
        return Color(0.0, 0.0, 0.0);
    }

    if (world.hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        return Color(0.0, 0.0, 0.0);
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

    auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<FuzzyMetal>(Color(0.8, 0.6, 0.2), 0.8);

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

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
