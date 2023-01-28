#pragma once

#include <hittable.h>

#include <memory>
#include <vector>


class HittableList: public Hittable {
    public:
        HittableList() {}
        HittableList(std::shared_ptr<Hittable> object) { add(object); }

        void clear();
        void add(std::shared_ptr<Hittable> object);

        virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;

    private:
        std::vector<std::shared_ptr<Hittable>> objects;
};
