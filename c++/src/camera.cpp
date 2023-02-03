#include <cmath>

#include <camera.h>
#include <utils.h>

Camera::Camera(
        const Point3 lookfrom,
        const Point3 lookat,
        const Vec3 vup,
        const float vfov,
        const float aspect_ratio
    ) {
    const auto theta = degrees_to_radians(vfov);
    const auto h = tan(theta / 2);

    const auto viewport_height = 2.0 * h;
    const auto viewport_width = aspect_ratio * viewport_height;

    const auto w = unit_vector(lookfrom - lookat);
    const auto u = unit_vector(cross(vup, w));
    const auto v = cross(w, u);

    origin = lookfrom;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lower_left_corner = origin
        - 0.5 * horizontal
        - 0.5 * vertical
        - w;
}

Ray Camera::getRay(float u, float v) const {
    return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}
