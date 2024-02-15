#pragma once

#include "../../Math/Vetor/Hexxy_Vector.h"
#include <vector>

namespace Hexxy { namespace Primitives { namespace Image {

	struct RGBA_Image;

	struct RGB_Image {
		RGB_Image()
			: width(0), height(0)
		{}
		RGB_Image(const RGBA_Image& image);
		~RGB_Image()
		{}
		size_t width;
		size_t height;
		std::vector<Hexxy::Math::Vectors::RGB_Color> data;
	};

	struct RGBA_Image {
		RGBA_Image()
			: width(0), height(0)
		{}
		RGBA_Image(const RGB_Image& image);
		~RGBA_Image()
		{}
		size_t width;
		size_t height;
		std::vector<Hexxy::Math::Vectors::RGBA_Color> data;
	};

} } }