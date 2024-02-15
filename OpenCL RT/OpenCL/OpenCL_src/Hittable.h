#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

typedef struct hit_record hit_record;
struct hit_record {
	vec3 p;
	vec3 normal;
	double t;
	bool front_face;
};

void hit_record_set_face_normal(hit_record* rec, ray r, vec3 outward_normal) {
	rec->front_face = vec3_dot(r.direction, outward_normal) < 0;
	rec->normal = rec->front_face ? outward_normal : vec3_minus(outward_normal);
}

typedef struct hittable hittable;
struct hittable {
	bool (*hit)(void* th, ray r, double t_min, double t_max, hit_record* rec);
};

hittable hittable_create()
{
	hittable o;
	o.hit = hittable_hit;
	return o;
}

bool hittable_hit(void* th, ray r, double t_min, double t_max, hit_record* rec) { return false; }

#endif