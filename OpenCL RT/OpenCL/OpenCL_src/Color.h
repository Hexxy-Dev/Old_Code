#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"

void write_color(vec3* pixel_color, unsigned char* image, const int image_width, const int image_height, const int ix, const int jy) {

	double r = pixel_color->x;
	double g = pixel_color->y;
	double b = pixel_color->z;

	r = 255.999 * r;
	g = 255.999 * g;
	b = 255.999 * b;

	image[ix * 4 + jy * image_width * 4 + 0] = r;
	image[ix * 4 + jy * image_width * 4 + 1] = g;
	image[ix * 4 + jy * image_width * 4 + 2] = b;
	image[ix * 4 + jy * image_width * 4 + 3] = 255;
}

#endif