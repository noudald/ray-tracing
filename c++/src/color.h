#pragma once

#include <iostream>

#include <vec3.h>
#include <utils.h>


void write_color(std::ostream &out, Color pixel_color, int samples_per_pixel) {
    auto r = pixel_color[0];
    auto g = pixel_color[1];
    auto b = pixel_color[2];

    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    out << static_cast<int>(254 * clamp(r, 0.0, 0.999)) << " "
        << static_cast<int>(254 * clamp(g, 0.0, 0.999)) << " "
        << static_cast<int>(254 * clamp(b, 0.0, 0.999)) << std::endl;
}
