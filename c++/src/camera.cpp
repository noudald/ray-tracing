#include <cmath>

#include <camera.h>
#include <utils.h>

Camera::Camera(
        const Point3 lookfrom,
        const Point3 lookat,
        const Vec3 vup,
        const float vfov,
        const float aspect_ratio,
        const float aperture,
        const float focus_dist
    ) {
    const auto theta = degrees_to_radians(vfov);
    const auto h = tan(theta / 2);

    const auto viewport_height = 2.0 * h;
    const auto viewport_width = aspect_ratio * viewport_height;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin
        - 0.5 * horizontal
        - 0.5 * vertical
        - focus_dist * w;

    lens_radius = 0.5 * aperture;
}

Ray Camera::getRay(float s, float t) const {
    const Vec3 rd = lens_radius * random_in_unit_sphere();
    Vec3 offset = rd[0] * u + rd[1] * v;

    return Ray(
        origin + offset,
        lower_left_corner + s*horizontal + t*vertical - origin - offset
    );
}
