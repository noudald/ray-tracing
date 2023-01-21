use crate::vec3::{Point, Vec3};

struct Ray {
    pub origin: Point,
    pub direction: Vec3
}


impl Ray {
    pub fn new(origin: &Point, direction: &Vec3) -> Self {
        Ray {
            origin: origin.clone(),
            direction: direction.clone()
        }
    }

    pub fn default() -> Self {
        Ray {
            origin: Point::new(0., 0., 0.),
            direction: Vec3::new(0., 0., 0.)
        }
    }

    pub fn at(&self, t: f32) -> Vec3 {
        &self.origin + &(t * &self.direction)
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_ray() {
        let ray1 = Ray::default();

        assert_eq!(ray1.origin.x, 0.0);
        assert_eq!(ray1.origin.y, 0.0);
        assert_eq!(ray1.origin.z, 0.0);
        assert_eq!(ray1.direction.x, 0.0);
        assert_eq!(ray1.direction.y, 0.0);
        assert_eq!(ray1.direction.z, 0.0);

        let ray2 = Ray::new(
            &Point::new(0., 0., 1.),
            &Vec3::new(1., 0.5, 1.)
        );

        let p1 = ray2.at(0.);
        let p2 = ray2.at(0.5);
        let p3 = ray2.at(1.);

        assert_eq!(p1.x, 0.);
        assert_eq!(p1.y, 0.);
        assert_eq!(p1.z, 1.);
        assert_eq!(p2.x, 0.5);
        assert_eq!(p2.y, 0.25);
        assert_eq!(p2.z, 1.5);
        assert_eq!(p3.x, 1.);
        assert_eq!(p3.y, 0.5);
        assert_eq!(p3.z, 2.);
    }
}
