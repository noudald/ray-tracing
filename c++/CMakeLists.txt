cmake_minimum_required(VERSION 3.10)
project(raytracing)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(vec3 src/vec3.h src/vec3.cpp)

target_include_directories(vec3 PUBLIC "src")

add_executable(raytracing src/main.cpp)
target_link_libraries(raytracing vec3)

add_executable(unittests src/unittests.cpp)
target_link_libraries(unittests vec3)
