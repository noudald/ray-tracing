#include <sphere.h>

bool Sphere::hit(const Ray &r, float t_min, float t_max, hit_record &rec) const {
    Vec3 oc = r.origin() - center;

    auto a = r.direction().length_squared();
    auto b = 2.0 * dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto disc = b*b - 4*a*c;

    if (disc < 0) {
        return false;
    }

    auto sqrtd = sqrt(disc);
    auto root = -(b + sqrtd) / (2*a);
    if (root < t_min || t_max < root) {
        root = -(b - sqrtd) / (2*a);
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}
