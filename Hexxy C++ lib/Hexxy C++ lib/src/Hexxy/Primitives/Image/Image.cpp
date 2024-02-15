#include "Image.h"

namespace Hexxy { namespace Primitives { namespace Image {

	RGB_Image::RGB_Image(const RGBA_Image& image)
	{
		width = image.width;
		height = image.height;
		data.reserve(width * height);
		for (size_t i = 0; i < data.size(); i++)
			data.emplace_back(0);
		for (size_t i = 0; i < data.size(); i++) {
			data[i].r = image.data[i].r;
			data[i].g = image.data[i].g;
			data[i].b = image.data[i].b;
		}
	}

	RGBA_Image::RGBA_Image(const RGB_Image& image)
	{
		width = image.width;
		height = image.height;
		data.reserve(width* height);
		for (size_t i = 0; i < data.size(); i++)
			data.emplace_back(0);
		for (size_t i = 0; i < data.size(); i++) {
			data[i].r = image.data[i].r;
			data[i].g = image.data[i].g;
			data[i].b = image.data[i].b;
			data[i].a = 255;
		}
	}
} } }