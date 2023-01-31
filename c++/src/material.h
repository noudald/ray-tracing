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
