mod vec3;
mod color;

use crate::vec3::Color;
use crate::color::write_color;

fn main() {
    let image_width = 256;
    let image_height = 256;

    println!("P3");
    println!("{} {}", image_width, image_height);
    println!("225");

    for i in 0..image_height {
        eprintln!("Processing line {}", i + 1);
        for j in 0..image_width {
            let pixel_color = Color {
                x: (i as f32) / ((image_height - 1) as f32),
                y: (j as f32) / ((image_width - 1) as f32),
                z: 0.25
            };

            write_color(&pixel_color);
        }
    }

    eprintln!("Finished processing");
}
