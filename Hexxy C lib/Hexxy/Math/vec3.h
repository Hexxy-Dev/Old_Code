#ifndef HEXXY_VEC3_H
#define HEXXY_VEC3_H

#include "../Macros.h"

#include <stdio.h>
//#include <immintrin.h>


typedef float VEC3_TYPE;

typedef struct vec3 vec3;
struct vec3 {
	VEC3_TYPE x;
	VEC3_TYPE y;
	VEC3_TYPE z;
};


#ifdef _INCLUDED_IMM
#else // _INCLUDED_IMM

#define vec3_create(...) VFUNC(vec3_create, __VA_ARGS__)
#define vec3_create vec3_create_VEC3_TYPE1
#define vec3_create3(X, Y) vec3_create_VEC3_TYPE3
vec3 vec3_create_VEC3_TYPE1(VEC3_TYPE x) {
	vec3 o;
	o.x = x;
	o.y = x;
	o.z = x;
	return o;
}
vec3 vec3_create_VEC3_TYPE3(VEC3_TYPE x, VEC3_TYPE y, VEC3_TYPE z) {
	vec3 o;
	o.x = x;
	o.y = y;
	o.z = z;
	return o;
}


vec3 vec3_invert_sign(vec3 v) {
	vec3 o;
	o.x = -v.x;
	o.y = -v.y;
	o.z = -v.z;
	return o;
}


#define vec3_add(...) TSFUNC2(vec3_add, vec3, VEC3_TYPE, __VA_ARGS__)
vec3 vec3_add_vec3(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.x + v1.x;
	o.y = v0.y + v1.y;
	o.z = v0.z + v1.z;
	return o;
}
vec3 vec3_add_VEC3_TYPE(vec3 v0, VEC3_TYPE t) {
	vec3 o;
	o.x = v0.x + t;
	o.y = v0.y + t;
	o.z = v0.z + t;
	return o;
}


#define vec3_subtract(...) TSFUNC2(vec3_subtract, vec3, VEC3_TYPE, __VA_ARGS__)
vec3 vec3_subtract_vec3(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.x - v1.x;
	o.y = v0.y - v1.y;
	o.z = v0.z - v1.z;
	return o;
}
vec3 vec3_subtract_VEC3_TYPE(vec3 v0, VEC3_TYPE t) {
	vec3 o;
	o.x = v0.x - t;
	o.y = v0.y - t;
	o.z = v0.z - t;
	return o;
}


#define vec3_multiply(...) TSFUNC2(vec3_multiply, vec3, VEC3_TYPE, __VA_ARGS__)
vec3 vec3_multiply_vec3(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.x * v1.x;
	o.y = v0.y * v1.y;
	o.z = v0.z * v1.z;
	return o;
}
vec3 vec3_multiply_VEC3_TYPE(vec3 v0, VEC3_TYPE t) {
	vec3 o;
	o.x = v0.x * t;
	o.y = v0.y * t;
	o.z = v0.z * t;
	return o;
}


#define vec3_divide(...) TSFUNC2(vec3_divide, vec3, VEC3_TYPE, __VA_ARGS__)
vec3 vec3_divide_vec3(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.x / v1.x;
	o.y = v0.y / v1.y;
	o.z = v0.z / v1.z;
	return o;
}
vec3 vec3_divide_VEC3_TYPE(vec3 v0, VEC3_TYPE t) {
	vec3 o;
	o.x = v0.x / t;
	o.y = v0.y / t;
	o.z = v0.z / t;
	return o;
}


float vec3_length_squared(vec3 v0) {
	return v0.x * v0.x + v0.y * v0.y + v0.z * v0.z;
}

float vec3_length(vec3 v0) {
	return sqrt(vec3_length_squared(v0));
}

float vec3_dot(vec3 v0, vec3 v1) {
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

vec3 vec3_cross(vec3 v0, vec3 v1) {
	vec3 o;
	o.x = v0.y * v1.z - v0.z * v1.y;
	o.y = v0.z * v1.x - v0.x * v1.z;
	o.z = v0.x * v1.y - v0.y * v1.x;
	return o;
}

vec3 vec3_unit_vector(vec3 v0) {
	return vec3_divide_VEC3_TYPE(v0, vec3_length(v0));
}


void vec3_print(vec3* v0) {
	printf("%f %f %f\n", v0->x, v0->y, v0->z);
}
#endif // !_INCLUDED_IMM

#endif // !HEXXY_VEC3_H
