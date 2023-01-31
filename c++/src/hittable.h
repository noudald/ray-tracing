#pragma once

#include <memory>

#include <vec3.h>
#include <ray.h>


class Material;


struct hit_record {
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> mat_ptr;
    float t;
    bool front_face;

    inline void set_face_normal(const Ray &r, const Vec3 &outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal: -outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};
