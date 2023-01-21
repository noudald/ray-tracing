mod vec3;
mod color;
mod ray;

use crate::vec3::{Color, Point, Vec3};
use crate::color::write_color;
use crate::ray::Ray;


fn hit_sphere(center: &Point, radius: f32, ray: &Ray) -> bool {
    let oc = ray.origin.clone() - center.clone();

    let a = ray.direction.dot(&ray.direction);
    let b = 2.0 * oc.dot(&ray.direction);
    let c = oc.dot(&oc) - radius*radius;

    let disc = b*b - 4.0*a*c;

    disc > 0.0
}


fn ray_color(r: &Ray) -> Color {
    if hit_sphere(&Vec3::new(0.0, 0.0, -1.0), 0.5, r) {
        return Color::new(1.0, 0.0, 0.0);
    }

    let unit_direction = r.direction.normalized();
    let t = 0.5 * (unit_direction.y + 1.0);

    (1.0 - t) * Color::new(1.0, 1.0, 1.0) + t * Color::new(0.5, 0.7, 1.0)
}


fn main() {
    // Image settings
    let aspect_ratio = 16.0 / 9.0;
    let image_width: u32 = 400;
    let image_height: u32 = (image_width as f32 / aspect_ratio) as u32;

    // Camera settings
    let viewport_width = 2.0;
    let viewport_height = viewport_width * aspect_ratio;
    let focal_length = 1.0;

    let origin = Point::zero();
    let horizontal = Vec3::new(viewport_width, 0.0, 0.0);
    let vertical = Vec3::new(0.0, viewport_height, 0.0);
    let lower_left_corner = origin.clone()
        - 0.5 * horizontal.clone()
        - 0.5 * vertical.clone()
        - Vec3::new(0.0, 0.0, focal_length);

    println!("P3");
    println!("{} {}", image_width, image_height);
    println!("225");

    for i in 0..image_height {
        eprintln!("Processing line {}", i + 1);
        for j in 0..image_width {
            let u = (i as f32) / ((image_height - 1) as f32);
            let v = (j as f32) / ((image_width - 1) as f32);

            let direction = lower_left_corner.clone()
                + u * horizontal.clone()
                + v * vertical.clone()
                - origin.clone();

            let pixel_color = ray_color(&Ray::new(&origin, &direction));

            write_color(&pixel_color);
        }
    }

    eprintln!("Finished processing");
}
