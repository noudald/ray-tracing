use crate::vec3::Color;

pub fn write_color(pixel_color: &Color) {
    let ir = (255.999 * pixel_color.x) as u32;
    let ig = (255.999 * pixel_color.y) as u32;
    let ib = (255.999 * pixel_color.z) as u32;

    println!("{} {} {}", ir, ig, ib);
}
