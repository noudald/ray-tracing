#include <iostream>
#include <cmath>

#include <vec3.h>

int num_tests = 0;

#define ASSERT(x) { \
    if (!(x)) { \
        std::cout << __FUNCTION__ \
            << " unit test failed on line " \
            << __LINE__ \
            << std::endl; \
        exit(1); \
    } \
    num_tests++; \
}
#define ASSERT_EQ(x, y) { \
    if (!((x) == (y))) { \
        std::cout << __FUNCTION__ \
            << " failed on line " \
            << __LINE__ \
            << ": " << x << " != " << y << "." << std::endl; \
        exit(1); \
    } \
    num_tests++; \
}
#define ASSERT_ALMOST_EQ(x, y) { \
    if (!(abs((x) - (y)) < 1e-7)) { \
        std::cout << __FUNCTION__ \
            << " failed on line " \
            << __LINE__ \
            << ": " << x << " != " << y << "." << std::endl; \
        exit(1); \
    } \
    num_tests++; \
}


void test_vec3() {
    Vec3 v1(1.0, 2.0, 3.0);
    Vec3 v2(1.0, 1.0, 1.0);

    ASSERT_EQ(v1.x(), 1.0);
    ASSERT_EQ(v1.y(), 2.0);
    ASSERT_EQ(v1.z(), 3.0);

    auto v3 = v1 + v2;

    ASSERT_EQ(v3[0], 2.0);
    ASSERT_EQ(v3[1], 3.0);
    ASSERT_EQ(v3[2], 4.0);

    auto v4 = v1 - v2;

    ASSERT_EQ(v4[0], 0.0);
    ASSERT_EQ(v4[1], 1.0);
    ASSERT_EQ(v4[2], 2.0);

    auto v5 = v1 * v2;

    ASSERT_EQ(v5[0], 1.0);
    ASSERT_EQ(v5[1], 2.0);
    ASSERT_EQ(v5[2], 3.0);

    auto v6 = unit_vector(v1);

    ASSERT_ALMOST_EQ(v6.length(), 1.0);

    auto f7 = dot(v1, v2);

    ASSERT_ALMOST_EQ(f7, 1.0 + 2.0 + 3.0);
}

int main() {
    test_vec3();
    std::cout << "All " << num_tests << " tests passed successful!" << std::endl;
}
