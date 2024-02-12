#pragma once

#include <cstring>
#include <utility>

namespace Hexxy
{
	namespace Data
	{
		template<typename T>
		struct array2Dbase
		{
			virtual const size_t size() const = 0;
			virtual const size_t sizeX() const = 0;
			virtual const size_t sizeY() const = 0;
			virtual const T* operator[](const size_t& index) const = 0;
		};

		template<typename T, size_t Y, size_t X>
		struct array2D : public array2Dbase<T>
		{
			array2D() { m_Data = new T[Y * X]; }
			~array2D() { delete[] m_Data; m_Data = nullptr; }

			void clear() { std::memset(m_Data, 0, (Y * X * sizeof(T))); }

			T* operator[](const size_t& index) { return &m_Data[X * index]; }
			const T* operator[](const size_t& index) const { return &m_Data[X * index]; }

			const size_t size() const { return X * Y; }
			const size_t sizeX() const { return X; }
			const size_t sizeY() const { return Y; }
			T* data() { return m_Data; }
			const T* data() const { return m_Data; }
		private:
			T* m_Data;
		};

		struct color
		{
			color()
				: R(0), G(0), B(0), A(1.0f)
			{}
			color(const uint8_t& R, const uint8_t& G, const uint8_t& B, const float& A = 1.0f)
				: R(R), G(G), B(B), A(A)
			{}
			~color() = default;

			uint8_t R, G, B;
			float A;
		};

		struct pixelColor
		{
			pixelColor()
				: R(0.0f), G(0.0f), B(0.0f), A(1.0f)
			{}
			pixelColor(Hexxy::Data::color& color)
				: R(float(color.R) / 255), G(float(color.G) / 255), B(float(color.B) / 255), A(color.A)
			{}
			~pixelColor() = default;

			float R, G, B, A;
		};

		struct ColorPaletteBase
		{
			virtual const color& operator[](const size_t& index) const = 0;
			virtual const size_t size() const = 0;
			virtual const pixelColor& getPixelColor(const size_t& index) const = 0;
		};

		template<size_t S>
		struct ColorPalette : public ColorPaletteBase
		{
			ColorPalette() { m_ColorData = new color[S]; m_pixelColorData = new pixelColor[S]; }
			~ColorPalette() { 
				delete[] m_ColorData; m_ColorData = nullptr;
				delete[] m_pixelColorData; m_pixelColorData = nullptr;
			}

			void set(const size_t& index, const uint8_t& R, const uint8_t& G, const uint8_t& B, const float& A = 1.0f)
			{
				m_ColorData[index] = std::move(color(R, G, B, A));
			}

			void set(const size_t& index, const color& newColor)
			{
				m_ColorData[index] = std::move(color(newColor.R, newColor.G, newColor.B, newColor.A));
			}

			void createPixelColors()
			{
				for (size_t i = 0; i < S; i++)
					m_pixelColorData[i] = std::move(pixelColor(m_ColorData[i]));
			}

			pixelColor& getPixelColor(const size_t& index) { return m_pixelColorData[index]; }
			const pixelColor& getPixelColor(const size_t& index) const { return m_pixelColorData[index]; }
			pixelColor* getPixelColorData() { return m_pixelColorData; }

			color& operator[](const size_t& index) { return m_ColorData[index]; }
			const color& operator[](const size_t& index) const { return m_ColorData[index]; }
			color* data() { return m_ColorData; }
			const size_t size() const { return S; }
		private:
			color* m_ColorData;
			pixelColor* m_pixelColorData;
		};
	}
}

struct Vertex
{
	float x, y;
	float r, g, b, a;
	~Vertex() = default;
};

struct Quad
{
	Vertex vertices[4];
	~Quad() = default;
};

