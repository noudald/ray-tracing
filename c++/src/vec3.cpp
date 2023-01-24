#include <iostream>

#include <vec3.h>

float dot(const Vec3 &u, const Vec3 &v) {
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}
