#ifndef VEC3_H
#define VEC3_H


typedef struct vec3 vec3;
struct vec3 {
	double x;
	double y;
	double z;
};

vec3 vec3_create(double x, double y, double z) {
	vec3 o;
	o.x = x;
	o.y = y;
	o.z = z;
	return o;
}

vec3 vec3_minus(vec3 v) {
	vec3 o;
	o.x = -v.x;
	o.y = -v.y;
	o.z = -v.z;
	return o;
}

vec3 vec3_add(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.x + v1.x;
	o.y = v0.y + v1.y;
	o.z = v0.z + v1.z;
	return o;
}

vec3 vec3_subtract(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.x - v1.x;
	o.y = v0.y - v1.y;
	o.z = v0.z - v1.z;
	return o;
}

vec3 vec3_multiply(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.x * v1.x;
	o.y = v0.y * v1.y;
	o.z = v0.z * v1.z;
	return o;
}
vec3 vec3_multiply_d(vec3 v0, double t) {
	vec3 o;
	o.x = v0.x * t;
	o.y = v0.y * t;
	o.z = v0.z * t;
	return o;
}

vec3 vec3_divide(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.x / v1.x;
	o.y = v0.y / v1.y;
	o.z = v0.z / v1.z;
	return o;
}
vec3 vec3_divide_d(vec3 v0, double t) {
	vec3 o;
	o.x = v0.x / t;
	o.y = v0.y / t;
	o.z = v0.z / t;
	return o;
}

double vec3_length_squared(vec3 v0) {
	return v0.x * v0.x + v0.y * v0.y + v0.z * v0.z;
}

double vec3_length(vec3 v0) {
	return sqrt(vec3_length_squared(v0));
}

double vec3_dot(vec3 v0,vec3 v1) {
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

vec3 vec3_cross(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.y * v1.z - v0.z * v1.y;
	o.y = v0.z * v1.x - v0.x * v1.z;
	o.z = v0.x * v1.y - v0.y * v1.x;
	return o;
}

struct vec3 vec3_unit_vector(struct vec3 v0) {
	return vec3_divide_d(v0, vec3_length(v0));
}


void vec3_print(struct vec3* v0) {
	printf("%f %f %f\n", v0->x, v0->y, v0->z);
}

#endif