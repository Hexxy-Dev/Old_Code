#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

typedef struct hittable_list hittable_list;
struct hittable_list {
    hittable base;
    hittable** objects;
    int size;
};

void hittable_list_create(hittable_list* list, int size) {
    list->objects = (hittable**)malloc(sizeof(hittable*) * size);
    list->base.hit = hittable_list_hit;
}

void hittable_list_add(hittable_list* list, int index, hittable* object) {
    list->objects[index] = (hittable*)malloc(sizeof(hittable));
    list->objects[index] = object;
}

bool hittable_list_hit(void* li, ray r, double t_min, double t_max, hit_record* rec) {
    hittable_list* list = (hittable_list*)li;
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (int i = 0; i < list->size; i++) {
        if (list->objects[i]->hit(list->objects[i], r, t_min, closest_so_far, &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif