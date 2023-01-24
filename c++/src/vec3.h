#pragma once

#include <cmath>

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
        }

        Vec3& operator*=(const float t) {
            vec[0] *= t;
            vec[1] *= t;
            vec[2] *= t;
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

    private:
        float vec[3];
};

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream &out, const Vec3 &vec) {
    return out << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
}

float dot(const Vec3 &u, const Vec3 &v);

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}
