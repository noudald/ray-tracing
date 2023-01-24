#include <iostream>

#include <vec3.h>


#define ASSERT(x) { \
    if (!(x)) { \
        std::cout << __FUNCTION__ \
            << " unit test failed on line " \
            << __LINE__ \
            << std::endl; \
        exit(1); \
    } \
}
#define ASSERT_EQ(x, y) { \
    if (!((x) == (y))) { \
        std::cout << __FUNCTION__ \
            << " failed on line " \
            << __LINE__ \
            << ": " << x << " != " << y << "." << std::endl; \
        exit(1); \
    } \
}

void test_vec3() {
    Vec3 v1(1.0, 2.0, 3.0);
    Vec3 v2(1.0, 1.0, 1.0);

    ASSERT_EQ(v1.x(), 1.0);
    ASSERT_EQ(v1.y(), 2.0);
    ASSERT_EQ(v1.z(), 3.0);

    Vec3 v3 = v1 + v2;

    ASSERT_EQ(v3[0], 2.0);
    ASSERT_EQ(v3[1], 3.0);
    ASSERT_EQ(v3[2], 4.0);
}

int main() {
    test_vec3();
}
