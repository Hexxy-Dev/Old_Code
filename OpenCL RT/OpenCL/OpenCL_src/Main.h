#ifndef MAIN_H
#define MAIN_H

#include "Common.h"

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"
#include "Hittable_list.h"
#include "Sphere.h"

vec3 ray_color(ray r, hittable_list* world) {
	hit_record rec;
	if(world->base.hit(world, r, 0, infinity, &rec))
		return vec3_multiply_d(vec3_add(rec.normal, vec3_create(1.0, 1.0, 1.0)), 0.5);

	vec3 unit_direction = vec3_unit_vector(r.direction);
	double t = 0.5 * (unit_direction.y + 1.0);

	vec3 color1 = vec3_create(1.0, 1.0, 1.0);
	vec3 color2 = vec3_create(0.5, 0.7, 1.0);
	
	return vec3_add(vec3_multiply_d(color1, (1.0 - t)), vec3_multiply_d(color2, t));
}

void Main(unsigned char* image, const int image_width, const int image_height, const int ix, const int jy)
{
	double aspect_ratio = (double)image_width / (double)image_height;
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;
	
	vec3 origin = vec3_create(0.0, 0.0, 0.0);
	vec3 horizontal = vec3_create(viewport_width, 0.0, 0.0);
	vec3 vertical = vec3_create(0.0, viewport_height, 0.0);
	vec3 focus = vec3_create(0.0, 0.0, focal_length);
	
	vec3 lower_left_corner = vec3_subtract(vec3_subtract(vec3_subtract(origin, vec3_divide_d(horizontal, 2)), vec3_divide_d(vertical, 2)), focus);

	
	double u = (double)ix / (image_width - 1);
	double v = (double)jy / (image_height - 1);

	ray r = ray_create(origin, vec3_subtract(vec3_add(vec3_add(lower_left_corner, vec3_multiply_d(horizontal, u)), vec3_multiply_d(vertical, v)), origin));
	
	hittable_list world;
	hittable_list_create(&world, 2);
	sphere sphere1 = sphere_create(vec3_create(0, 0, -1), 0.5);
	sphere sphere2 = sphere_create(vec3_create(0, -100.5, -1), 100);
	hittable_list_add(&world, 0, &sphere1.base);
	hittable_list_add(&world, 0, &sphere2.base);

	vec3 color = ray_color(r, &world);

	write_color(&color, image, image_width, image_height, ix, jy);
}

#endif