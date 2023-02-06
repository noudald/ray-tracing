#include <execution>
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

    if (world.hit(r, 0.0001, infinity, rec)) {
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


HittableList random_scene() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3(0.0, -1000.0, 0.0), 1000.0, ground_material));

    for (auto a = -11; a < 11; a++) {
        for (auto b = -11; b < 11; b++) {
            const auto choose_mat = random_float();
            Point3 center(a + 0.9*random_float(), 0.2, b + 0.9*random_float());

            if ((center - Point3(4.0, 0.2, 0.0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    const auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                } else if (choose_mat < 0.95) {
                    const auto albedo = Color::random(0.5, 1.0);
                    const auto fuzz = random_float(0, 0.5);
                    sphere_material = std::make_shared<FuzzyMetal>(albedo, fuzz);
                } else {
                    sphere_material = std::make_shared<Dielectric>(1.5);
                }

                world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
            }
        }
    }

    const auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 1.0, material1));

    const auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, material2));

    const auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5));
    world.add(std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, material3));

    return world;
}


struct compute_params {
    std::shared_ptr<HittableList> world;
    std::shared_ptr<Camera> camera;
    int i;
    int j;
    int samples_per_pixel;
    int image_width;
    int image_height;
    Color pixel_color;
};


Color render_point(compute_params &params) {
    auto i = params.i;
    auto j = params.j;
    auto image_width = params.image_width;
    auto image_height = params.image_height;
    auto samples_per_pixel = params.samples_per_pixel;
    auto camera = params.camera;
    auto world = params.world;

    Color pixel_color(0.0, 0.0, 0.0);
    for (int s = 0; s < samples_per_pixel; s++) {
        auto u = (float(i) + random_float()) / (image_width - 1);
        auto v = (float(j) + random_float()) / (image_height - 1);

        auto r = (*camera).getRay(u, v);
        pixel_color += ray_color(r, *world);
    }

    return pixel_color;
}


int main() {
    // Image settings.
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;

    // Camera
    const Point3 look_from(13.0, 2.0, 3.0);
    const Point3 look_at(0.0, 0.0, 0.0);
    const Vec3 vup(0.0, 1.0, 0.0);
    const auto dist_to_focus = 10.0;
    const auto aperture = 0.1;

    Camera camera(
        look_from,
        look_at,
        vup,
        20,
        aspect_ratio,
        aperture,
        dist_to_focus
    );

    // World
    auto world = random_scene();

    // Render Image.
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    compute_params params = {
        .world = std::make_shared<HittableList>(world),
        .camera = std::make_shared<Camera>(camera),
        .i = 0,
        .j = 0,
        .samples_per_pixel = samples_per_pixel,
        .image_width = image_width,
        .image_height = image_height,
        .pixel_color = Color(0.0, 0.0, 0.0)
    };

    std::vector<compute_params> vparams;
    for (int j = image_height - 1; j >= 0; j--) {
        for (int i = 0; i < image_width; i++) {
            compute_params params = {
                .world = std::make_shared<HittableList>(world),
                .camera = std::make_shared<Camera>(camera),
                .i = i,
                .j = j,
                .samples_per_pixel = samples_per_pixel,
                .image_width = image_width,
                .image_height = image_height,
            };
            vparams.push_back(params);
        }
    }

    std::for_each(
        std::execution::par,
        vparams.begin(),
        vparams.end(),
        [](compute_params &params) {
            params.pixel_color = render_point(params);
        }
    );

    for (auto &params: vparams) {
            write_color(std::cout, params.pixel_color, samples_per_pixel);
    }
}
