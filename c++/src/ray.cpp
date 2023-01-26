#include <ray.h>


Point3 Ray::origin() const {
    return org;
}

Vec3 Ray::direction() const {
    return dir;
}

Point3 Ray::at(float t) const {
    return org + t * dir;
}
