#pragma once

#include <ray.h>
#include <utils.h>
#include <vec3.h>


struct hit_record;


class Material {
    public:
        virtual bool scatter(
            const Ray &r_in,
            const hit_record &rec,
            Color &attenuation,
            Ray &scattered
        ) const = 0;
};


class Lambertian: public Material {
    public:
        Lambertian(const Color &a): albedo(a) {}

        virtual bool scatter(
            const Ray &r_in,
            const hit_record &rec,
            Color &attenuation,
            Ray &scattered
        ) const override {
            auto scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero()) {
                scatter_direction = rec.normal;
            }

            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    private:
        Color albedo;
};


class Metal: public Material {
    public:
        Metal(const Color &a): albedo(a) { }

        virtual bool scatter(
            const Ray &r_in,
            const hit_record &rec,
            Color &attenuation,
            Ray &scattered
        ) const override {
            auto reflected = reflect(unit_vector(r_in.direction()), rec.normal);

            scattered = Ray(rec.p, reflected);
            attenuation = albedo;

            return (dot(scattered.direction(), rec.normal) > 0);
        }

    private:
        Color albedo;
};


class FuzzyMetal: public Material {
    public:
        FuzzyMetal(const Color &a, float f): albedo(a), fuzz(f < 1 ? f : 1) { }

        virtual bool scatter(
            const Ray &r_in,
            const hit_record &rec,
            Color &attenuation,
            Ray &scattered
        ) const override {
            auto reflected = reflect(unit_vector(r_in.direction()), rec.normal);

            scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;

            return (dot(scattered.direction(), rec.normal) > 0);
        }

    private:
        Color albedo;
        float fuzz;
};


class Dielectric: public Material {
    public:
        Dielectric(float index_of_refraction): ir(index_of_refraction) {}

        virtual bool scatter(
            const Ray &r_in,
            const hit_record &rec,
            Color &attenuation,
            Ray &scattered
        ) const override {
            attenuation = Color(1.0, 1.0, 1.0);
            float refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

            Vec3 unit_direction = unit_vector(r_in.direction());
            float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            float sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            Vec3 direction;
            if ((refraction_ratio * sin_theta > 1.0)
                    || (reflectance(cos_theta, refraction_ratio) > random_float())) {
                direction = reflect(unit_direction, rec.normal);
            } else {
                direction = refract(unit_direction, rec.normal, refraction_ratio);
            }

            scattered = Ray(rec.p, direction);

            return true;
        }

    private:
        float ir;  // Index of reflection.

        static float reflectance(float cosine, float ref_idx) {
            auto r0 = pow((1 - ref_idx) / (1 + ref_idx), 2);
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }
};
