#pragma once

#include <cstring>
#include <utility>
#include <vector>

namespace Hexxy
{
	namespace Data
	{
		/// <summary>
		/// <para>A unsined char 2D array (no negative numbers and a max limit of 255)</para>
		/// <para>This is a 2D array that is used to create the Buffer<para>
		/// This is a heap allocated array ( allocated in a continnuous block of memory )
		/// </summary>
		struct array2D
		{
			/// <summary>
			/// Creates a 2D array
			/// </summary>
			/// <param name="Y">size ( i )</param>
			/// <param name="X">size ( j )</param>
			array2D(size_t Y, size_t X)
				: Y(Y), X(X)
			{
				m_Data = new uint8_t [Y * X];
				updated.reserve(Y + 1);
				for (size_t i = 0; i < Y + 1; i++)
					updated.emplace_back(0);
			}

			~array2D() { delete[] m_Data; m_Data = nullptr; }

			/// <summary>
			/// Sets all data in the array to be 0
			/// </summary>
			void clear() { std::memset(m_Data, 0, (Y * X * sizeof(uint8_t))); }

			uint8_t* operator[](const size_t& index)
			{
				updated[index] = 1;
				return &m_Data[X * index];
			}
			const uint8_t* operator[](const size_t& index) const { return &m_Data[X * index]; }

			
			/// <summary>
			/// </summary>
			/// <returns>The total size of the array</returns>
			const size_t size() const { return X * Y; }

			/// <summary>
			/// </summary>
			/// <returns>The X ( j ) size of the array</returns>
			const size_t sizeX() const { return X; }

			/// <summary>
			/// </summary>
			/// <returns>The Y ( i ) size of the array</returns>
			const size_t sizeY() const { return Y; }

			/// <summary>
			/// Function that returns the pointer to the actual memory ( 1D array )
			/// </summary>
			/// <returns>a pointer to a 1D array</returns>
			uint8_t* data() { return m_Data; }

			/// <summary>
			/// Const function that returns the pointer to the actual memory ( 1D array )
			/// </summary>
			/// <returns>a pointer to a 1D array</returns>
			const uint8_t* data() const { return m_Data; }

			mutable std::vector<bool> updated;

			/// <summary>
			/// Function used to fill the "updated" vector with 1
			/// </summary>
			void UpdateAll()
			{
				for (size_t i = 0; i < Y + 1; i++)
					updated[i] = 1;
			}
		private:
			uint8_t* m_Data;
			size_t Y, X;
		};

		/// <summary>
		/// Simple data structure to hold RGBA values
		/// </summary>
		struct color
		{
			color()
				: R(0), G(0), B(0), A(255)
			{ compress(); }
			color(const uint8_t& R, const uint8_t& G, const uint8_t& B, const uint8_t& A = 255, const unsigned int& compressed = 0)
				: R(R), G(G), B(B), A(A), compressed(compressed)
			{ /*compress();//*/ }
			~color() = default;
			void compress() { compressed = (A << 24) | (B << 16) | (G << 8) | (R); }

			uint8_t R, G, B, A;
			unsigned int compressed;
		};

		/// <summary>
		/// 1D array that holds color values
		/// </summary>
		struct ColorPalette
		{
			/// <summary>
			/// Creates a 1D array of colors with the given size 
			/// </summary>
			/// <param name="Size"></param>
			ColorPalette(size_t Size)
				: Size(Size)
			{ m_ColorData = new color[Size]; }

			~ColorPalette() { delete[] m_ColorData; m_ColorData = nullptr; }

			/// <summary>
			/// Set the RGBA values of a color at a given index
			/// </summary>
			/// <param name="index"></param>
			/// <param name="R"></param>
			/// <param name="G"></param>
			/// <param name="B"></param>
			/// <param name="A">- value between 0 and 1 (optional)</param>
			void set(const size_t& index, const uint8_t& R, const uint8_t& G, const uint8_t& B, const uint8_t& A = 255)
			{
				m_ColorData[index] = std::move(color(R, G, B, A, m_ColorData[index].compressed));
			}

			/// <summary>
			/// Set the color at a given index using a color object
			/// </summary>
			/// <param name="index"></param>
			/// <param name="newColor"> - color object</param>
			void set(const size_t& index, const color& newColor)
			{
				m_ColorData[index] = std::move(color(newColor.R, newColor.G, newColor.B, newColor.A, m_ColorData[index].compressed));
			}

			/// <summary>
			/// Set the RGBA value of the Background behind the buffer (can be used for playing around with
			/// the transparency of the Buffer's "pixels")
			/// </summary>
			/// <param name="R"></param>
			/// <param name="G"></param>
			/// <param name="B"></param>
			/// <param name="A">- float value between 0 and 1 (optional) should be 1 tough :)</param>
			void SetClearColor(const uint8_t& R, const uint8_t& G, const uint8_t& B, const uint8_t& A = 255)
			{
				m_ClearColor.R = R;
				m_ClearColor.G = G;
				m_ClearColor.B = B;
				m_ClearColor.A = A;
				m_ClearColor.compress();
			}

			/// <summary>
			/// Update the compressed colors
			/// </summary>
			void CreateCompressedColor()
			{
				for (short i = 0; i < Size; i++)
					m_ColorData[i].compress();
			}

			color& operator[](const size_t& index) { return m_ColorData[index]; }
			const color& operator[](const size_t& index) const { return m_ColorData[index]; }

			/// <summary>
			/// Function that retrives the pointer to the 1D color array
			/// </summary>
			/// <param name="index"></param>
			/// <returns>pointer to a 1D color array</returns>
			color* data() { return m_ColorData; }

			/// <summary>
			/// Const function that retrives the pointer to the 1D pixelColor array
			/// </summary>
			/// <param name="index"></param>
			/// <returns>pointer to a 1D pixelColor array</returns>
			const size_t size() const { return Size; }

			color m_ClearColor;
		private:
			color* m_ColorData;
			size_t Size;
		};
	}
}

