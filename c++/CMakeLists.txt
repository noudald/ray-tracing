cmake_minimum_required(VERSION 3.10)
project(raytracing)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(vec3 src/vec3.h src/vec3.cpp)
add_library(ray src/ray.h src/ray.cpp)
add_library(sphere src/sphere.h src/sphere.cpp)
add_library(hittable_list src/hittable_list.h src/hittable_list.cpp)

target_include_directories(vec3 PUBLIC "src")
target_include_directories(ray PUBLIC "src")
target_include_directories(sphere PUBLIC "src")
target_include_directories(hittable_list PUBLIC "src")

add_executable(raytracing src/main.cpp src/color.h src/utils.h src/hittable.h)
target_link_libraries(raytracing vec3 ray sphere hittable_list)

add_executable(tests src/tests.cpp)
target_link_libraries(tests vec3)
