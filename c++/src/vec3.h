#pragma once

#include <ostream>
#include <cmath>

#include <utils.h>

using std::sqrt;

class Vec3 {
    public:
        Vec3(): vec{0, 0, 0} {}

        Vec3(float e0, float e1, float e2): vec{e0, e1, e2} {}

        float x() const {
            return vec[0];
        }

        float y() const {
            return vec[1];
        }

        float z() const {
            return vec[2];
        }

        Vec3 operator-() const {
            return Vec3(-vec[0], -vec[1], -vec[2]);
        }

        float operator[](int i) const {
            return vec[i];
        }

        float& operator[](int i) {
            return vec[i];
        }

        Vec3& operator+=(const Vec3 &other) {
            vec[0] += other[0];
            vec[1] += other[1];
            vec[2] += other[2];

            return *this;
        }

        Vec3& operator*=(const float t) {
            vec[0] *= t;
            vec[1] *= t;
            vec[2] *= t;

            return *this;
        }

        Vec3& operator/=(const float t) {
            return *this *= 1/t;
        }

        float dot(const Vec3 &other) {
            return vec[0]*other[0] + vec[1]*other[1] + vec[2]*other[2];
        }

        float length_squared() const {
            return vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
        }

        float length() const {
            return sqrt(length_squared());
        }

        inline static Vec3 random() {
            return Vec3(random_float(), random_float(), random_float());
        }

        inline static Vec3 random(float min, float max) {
            return Vec3(random_float(min, max), random_float(min, max), random_float(min, max));
        }

        bool near_zero() const {
            const auto s = 1e-6;
            return (fabs(vec[0]) < s) && (fabs(vec[1]) < s) && (fabs(vec[2]) < s);
        }

    private:
        float vec[3];
};


using Point3 = Vec3;
using Color = Vec3;


inline std::ostream& operator<<(std::ostream &out, const Vec3 &vec) {
    return out << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vec3 operator*(float t, const Vec3 &u) {
    return Vec3(t * u[0], t * u[1], t * u[2]);
}

inline Vec3 operator*(const Vec3 &u, float t) {
    return t * u;
}

inline Vec3 operator/(const Vec3 &u, float t) {
    return (1.0 / t) * u;
}

inline float dot(const Vec3 &u, const Vec3 &v) {
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0]);
}

inline Vec3 unit_vector(Vec3 u) {
    return u / u.length();
}


inline Vec3 random_in_unit_sphere() {
    while (true) {
        auto p = Vec3::random(-1.0, 1.0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline Vec3 reflect(const Vec3 &v, const Vec3 &n) {
    return v - 2 * dot(v, n) * n;
}
