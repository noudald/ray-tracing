#pragma once

#include <ray.h>
#include <vec3.h>

class Camera {
    public:
        Camera();

        Ray getRay(float u, float v) const;

    private:
        Point3 origin;
        Point3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
};
