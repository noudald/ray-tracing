mod vec3;
mod color;

use crate::vec3::Color;
use crate::color::write_color;


fn main() {
    // Image
    let image_width = 256;
    let image_height = 256;

    // Render
    print!("P3\n{} {}\n255\n", image_width, image_height);
    for j in (0..image_height).rev() {
        if j % (image_height / 10) == 0 {
            eprint!(".");
        }
        for i in 0..image_width {
            let r = i as f32 / ((image_width - 1) as f32);
            let g = j as f32 / ((image_height - 1) as f32);
            let b = 0.25;

            let pixel_color = Color::new(r, g, b);

            write_color(&pixel_color);
        }
    }

    eprint!("\n");
}
