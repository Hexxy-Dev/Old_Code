#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

typedef struct sphere sphere;
struct sphere {
	hittable base;
	vec3 center;
	double radius;
};

sphere sphere_create(vec3 cen, double r)
{
	sphere o;
	o.base = hittable_create();
	o.base.hit = sphere_hit;
	o.center = cen;
	o.radius = r;
	return o;
}

bool sphere_hit(void* th, ray r, double t_min, double t_max, hit_record* rec) {

	sphere* s = (sphere*)th;
	vec3 oc = vec3_subtract(r.origin, s->center);
	double a = vec3_length_squared(r.direction);
	double half_b = vec3_dot(oc, r.direction);
	double c = vec3_length_squared(oc) - s->radius * s->radius;

	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return false;

	auto sqrtd = sqrt(discriminant);

	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec->t = root;
	rec->p = ray_at(r, rec->t);
	vec3 outward_normal = vec3_divide_d(vec3_subtract(rec->p, s->center), s->radius);
	hit_record_set_face_normal(rec, r, outward_normal);

	return true;
}

#endif