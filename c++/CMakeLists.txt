cmake_minimum_required(VERSION 3.10)
project(raytracing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(TBB REQUIRED)

add_library(vec3 src/vec3.h src/vec3.cpp)
add_library(ray src/ray.h src/ray.cpp)
add_library(sphere src/sphere.h src/sphere.cpp)
add_library(hittable_list src/hittable_list.h src/hittable_list.cpp)
add_library(camera src/camera.h src/camera.cpp)

target_include_directories(vec3 PUBLIC "src")
target_include_directories(ray PUBLIC "src")
target_include_directories(sphere PUBLIC "src")
target_include_directories(hittable_list PUBLIC "src")
target_include_directories(camera PUBLIC "src")

add_executable(raytracing src/main.cpp src/color.h src/utils.h src/hittable.h)
target_link_libraries(raytracing vec3 ray sphere hittable_list camera tbb)

add_executable(tests src/tests.cpp)
target_link_libraries(tests vec3)
