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

            let ir = (255.999 * r) as u32;
            let ig = (255.999 * g) as u32;
            let ib = (255.999 * b) as u32;

            print!("{} {} {}\n", ir, ig, ib);
        }
    }

    eprint!("\n");
}
