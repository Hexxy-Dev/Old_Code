#pragma once

#include "DataTypes.h"

#include <iostream>

namespace Hexxy
{
	namespace Utility
	{
		void printColorValues(Hexxy::Data::color color)
		{
			std::cout << "Color: " << (int)color.R << ", " << (int)color.G << ", " << (int)color.B << ", " << color.A << '\n';
		}

		void printColorValues(Hexxy::Data::color color, size_t i)
		{
			std::cout << "Color " << i << ": " << (int)color.R << ", " << (int)color.G << ", " << (int)color.B << ", " << color.A << '\n';
		}

		void printColorPalette(const Hexxy::Data::ColorPalette& palette)
		{
			std::cout << "Palette contents:\n";

			for (size_t i = 0; i < palette.size(); i++)
			{
				printColorValues(palette[i], i);
			}
			std::cout << "End of Palette\n";
		}

		void printBuffer(Hexxy::Data::array2D& buffer)
		{
			std::cout << "Buffer contents:\n";

			for (size_t i = 0; i < buffer.sizeY(); i++)
			{
				for (size_t j = 0; j < buffer.sizeX(); j++)
				{
					std::cout << (int)buffer[i][j] << ' ';
				}
				std::cout << '\n';
			}
			std::cout << "End of Buffer\n";
		}
	}
}
