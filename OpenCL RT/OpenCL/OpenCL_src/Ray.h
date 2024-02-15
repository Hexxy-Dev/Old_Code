#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

typedef struct ray ray;
struct ray {
	struct vec3 origin;
	struct vec3 direction;
};

ray ray_create(vec3 origin, vec3 direction) {
	ray o;
	o.origin = origin;
	o.direction = direction;
	return o;
}

vec3 ray_at(ray r, double t) {
	return vec3_add(r.origin, vec3_multiply_d(r.direction, t));
}

#endif