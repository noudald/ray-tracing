use std::ops;

#[derive(Clone, Debug)]
pub struct Vec3 {
    pub x: f32,
    pub y: f32,
    pub z: f32
}

impl ops::Add<&Vec3> for &Vec3 {
    type Output = Vec3;

    fn add(self, other: &Vec3) -> Vec3 {
        Vec3 {
            x: self.x + other.x,
            y: self.y + other.y,
            z: self.z + other.z
        }
    }
}

impl ops::Sub<&Vec3> for &Vec3 {
    type Output = Vec3;

    fn sub(self, other: &Vec3) -> Vec3 {
        Vec3 {
            x: self.x - other.x,
            y: self.y - other.y,
            z: self.z - other.z
        }
    }
}

impl ops::Mul<f32> for &Vec3 {
    type Output = Vec3;

    fn mul(self, other: f32) -> Vec3 {
        Vec3 {
            x: self.x * other,
            y: self.y * other,
            z: self.z * other
        }
    }
}

impl ops::Mul<&Vec3> for f32 {
    type Output = Vec3;

    fn mul(self, other: &Vec3) -> Vec3 {
        other * self
    }
}

impl ops::Mul<&Vec3> for &Vec3 {
    type Output = Vec3;

    fn mul(self, other: &Vec3) -> Vec3 {
        Vec3 {
            x: self.x * other.x,
            y: self.y * other.y,
            z: self.z * other.z
        }
    }
}

impl Vec3 {
    pub fn new(x: f32, y: f32, z: f32) -> Self {
        Vec3 {x, y, z}
    }

    pub fn zero() -> Self {
        Vec3::new(0.0, 0.0, 0.0)
    }

    pub fn dot(&self, other: &Vec3) -> f32 {
        self.x*other.x + self.y*other.y + self.z*other.z
    }

    pub fn length(&self) -> f32 {
        self.dot(&self).sqrt()
    }

    pub fn cross(&self, other: &Vec3) -> Vec3 {
        Vec3 {
            x: self.y*other.z - self.z*other.y,
            y: self.z*other.x - self.x*other.z,
            z: self.x*other.y - self.y*other.x
        }
    }
}


pub use Vec3 as Color;
pub use Vec3 as Point;


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_vec3() {
        let v1 = Vec3::new(1., 2., 3.);
        let v2 = 2. * &v1;
        let v3 = &v1 * 2.;

        assert_eq!(v2.x, 2.*v1.x);
        assert_eq!(v2.y, 2.*v1.y);
        assert_eq!(v2.z, 2.*v1.z);
        assert_eq!(v2.x, v3.x);
        assert_eq!(v2.y, v3.y);
        assert_eq!(v2.z, v3.z);

        let v4 = Vec3::new(1., 1., 1.);
        let v5 = &v1 - &v4;

        assert_eq!(v5.x, 0.);
        assert_eq!(v5.y, 1.);
        assert_eq!(v5.z, 2.);

        let v6 = &v1 * &v1;

        assert_eq!(v6.x, 1.);
        assert_eq!(v6.y, 4.);
        assert_eq!(v6.z, 9.);

        let v7 = &v1 + &v4;

        assert_eq!(v7.x, 2.);
        assert_eq!(v7.y, 3.);
        assert_eq!(v7.z, 4.);

        assert_eq!(v4.length(), 3_f32.sqrt());
        assert_eq!(v4.dot(&v1), 6_f32);
    }
}
