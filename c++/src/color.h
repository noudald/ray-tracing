#pragma once

#include <iostream>

#include <vec3.h>


void write_color(std::ostream &out, Color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color[0]) << " "
        << static_cast<int>(255.999 * pixel_color[1]) << " "
        << static_cast<int>(255.999 * pixel_color[2]) << std::endl;
}
