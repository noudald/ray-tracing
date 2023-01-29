#pragma once

#include <limits>
#include <random>

const float infinity = std::numeric_limits<float>::infinity();


inline float random_float() {
    static std::uniform_real_distribution<float> dist(0.0, 1.0);
    static std::mt19937 generator;
    return dist(generator);
}

inline float random_float(float min, float max) {
    static std::uniform_real_distribution<float> dist(min, max);
    static std::mt19937 generator;
    return dist(generator);
}

inline float clamp(float x, float min, float max) {
    if (x < min) {
        return min;
    }
    if (max < x) {
        return max;
    }
    return x;
}
