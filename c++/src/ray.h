#pragma once

#include <vec3.h>

class Ray {
public:
    Ray() {}

    Ray(const Point3 &origin, const Vec3 &direction): org(origin), dir(direction) { }

    Point3 origin() const;
    Vec3 direction() const;
    Point3 at(float t) const;

private:
    Point3 org;
    Vec3 dir;
};
