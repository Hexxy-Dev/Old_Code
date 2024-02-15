#pragma once

#include "Globals.h"

void write_color(color pixel_color, int samples_per_pixel, size_t texture_index_H, size_t texture_index_W)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	if (r != r) r = 0.0;
	if (g != g) g = 0.0;
	if (b != b) b = 0.0;

	auto scale = 1.0 / samples_per_pixel;

	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);

	image[texture_index_H][texture_index_W][0] = static_cast<GLubyte>(static_cast<int>(256 * clamp(r, 0.0, 0.999)));
	image[texture_index_H][texture_index_W][1] = static_cast<GLubyte>(static_cast<int>(256 * clamp(g, 0.0, 0.999)));
	image[texture_index_H][texture_index_W][2] = static_cast<GLubyte>(static_cast<int>(256 * clamp(b, 0.0, 0.999)));
	image[texture_index_H][texture_index_W][3] = static_cast<GLubyte>(255);
}