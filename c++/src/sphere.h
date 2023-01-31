#pragma once

#include <hittable.h>
#include <material.h>
#include <vec3.h>


class Sphere: public Hittable {
    public:
        Sphere() {}

        Sphere(Point3 cen, float r, std::shared_ptr<Material> m)
            : center(cen), radius(r), mat_ptr(m) {};

        virtual bool hit(
            const Ray &r,
            float t_min,
            float t_max,
            hit_record &rec
        ) const override;

    private:
        Point3 center;
        float radius;
        std::shared_ptr<Material> mat_ptr;
};
