#pragma once

#include "Mat.h"

namespace Hexxy { namespace Math { namespace Matrix {

	inline auto CalculateDeterminant(const Hexxy::Math::Matrix::Mat2& mat)
	{
		return mat.x11 * mat.x22 - mat.x21 * mat.x12;
	}
	inline auto CalculateDeterminant(const Hexxy::Math::Matrix::Mat3& mat)
	{
		return mat.x11 * mat.x22 * mat.x33 + mat.x13 * mat.x21 * mat.x32 + mat.x31 * mat.x12 * mat.x23
			 - mat.x31 * mat.x22 * mat.x13 - mat.x11 * mat.x32 * mat.x23 - mat.x33 * mat.x12 * mat.x21;
	}
	inline auto CalculateDeterminant(const Hexxy::Math::Matrix::Mat4& mat)
	{
		return	mat.x11 * mat.x22 * mat.x33 * mat.x44 - mat.x11 * mat.x22 * mat.x34 * mat.x43
			  - mat.x11 * mat.x23 * mat.x32 * mat.x44 + mat.x11 * mat.x23 * mat.x34 * mat.x42
			  + mat.x11 * mat.x24 * mat.x32 * mat.x43 - mat.x11 * mat.x24 * mat.x33 * mat.x42
			  - mat.x12 * mat.x21 * mat.x33 * mat.x44 + mat.x12 * mat.x21 * mat.x34 * mat.x43
			  + mat.x12 * mat.x23 * mat.x31 * mat.x44 - mat.x12 * mat.x23 * mat.x34 * mat.x41
			  - mat.x12 * mat.x24 * mat.x31 * mat.x43 + mat.x12 * mat.x24 * mat.x33 * mat.x41
			  + mat.x13 * mat.x21 * mat.x32 * mat.x44 - mat.x13 * mat.x21 * mat.x34 * mat.x42
			  - mat.x13 * mat.x22 * mat.x31 * mat.x44 + mat.x13 * mat.x22 * mat.x34 * mat.x41
			  + mat.x13 * mat.x24 * mat.x31 * mat.x42 - mat.x13 * mat.x24 * mat.x32 * mat.x41
			  - mat.x14 * mat.x21 * mat.x32 * mat.x43 + mat.x14 * mat.x21 * mat.x33 * mat.x42
			  + mat.x14 * mat.x22 * mat.x31 * mat.x43 - mat.x14 * mat.x22 * mat.x33 * mat.x41
			  - mat.x14 * mat.x23 * mat.x31 * mat.x42 + mat.x14 * mat.x23 * mat.x32 * mat.x41;
	}

} } }