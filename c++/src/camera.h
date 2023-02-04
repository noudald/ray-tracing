#pragma once

#include <ray.h>
#include <vec3.h>

class Camera {
    public:
        Camera(
            const Point3 lookfrom,
            const Point3 lookat,
            const Vec3 vup,
            const float vfov,
            const float aspect_ratio,
            const float aperture,
            const float focus_dist
        );

        Ray getRay(float s, float t) const;

    private:
        Point3 origin;
        Point3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 u, w, v;
        float lens_radius;
};
