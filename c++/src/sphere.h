#pragma once

#include <hittable.h>
#include <vec3.h>


class Sphere: public Hittable {
    public:
        Sphere() {}

        Sphere(Point3 cen, float r): center(cen), radius(r) {};

        virtual bool hit(
            const Ray &r,
            float t_min,
            float t_max,
            hit_record &rec
        ) const override;

    private:
        Point3 center;
        float radius;
};
