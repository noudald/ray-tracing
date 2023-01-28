#include <hittable_list.h>


void HittableList::clear() {
    objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object) {
    objects.push_back(object);
}

bool HittableList::hit(const Ray &r, float t_min, float t_max, hit_record &rec) const {
    hit_record temp_rec;

    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object: objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
