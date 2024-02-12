#pragma once

#include "Settings.h"

#include "Input.h"
#include "Audio.h"

#include "DataTypes.h"

#include <atomic>

namespace Hexxy
{
	extern std::atomic_bool Fixed_Update_OK;

	/// <summary>
	/// <para>WIP this function can be really unsafe and can causes massive memory leaks</para>
	/// Calls a function on a periodic basis (function is called in a new thread so atomic variable should be used)
	/// </summary>
	/// <param name="function">- pointer to function to be called</param>
	void Set_Fixed_Update_Function(void (*function)());

	/// <summary>
	/// <para>WIP</para>
	/// <para>Fixed Uppdate Function HAS to set the Hexxy::Fixed_Update_OK var to false for the program to wait</para>
	/// Stops the current thread until the Fixed Update sets a bool that it is ok to continue
	/// </summary>
	void Wait_Fixed_Update();

	/// <summary>
	/// Efficient thread sleep function
	/// </summary>
	/// <param name="seconds"></param>
	void Sleep_For_Seconds(const size_t& seconds);

	/// <summary>
	/// Efficient thread sleep function
	/// </summary>
	/// <param name="milliseconds"></param>
	void Sleep_For_Milliseconds(const size_t& milliseconds);

	/// <summary>
	/// <para>This class creates a display object and runs all necessary code for initialization</para>
	/// WARNING: multiple displays are not supported!!!
	/// </summary>
	class Display
	{
	public:
		/// <summary>
		/// Creates a display objects and runs initialization
		/// </summary>
		/// <param name="Y">(The height of the Buffer)( i )</param>
		/// <param name="X">(The width of the Buffer)( j )</param>
		/// <param name="colors">(How many colors the Display will be able to create)</param>
		Display(const size_t& Y, const size_t& X, const size_t& colors)
			: Buffer(Y, X), ColorPalette(colors), Y(Y), X(X), m_Y_Offset(0), m_X_Offset(0)
		{ init(); }

		/// <summary>
		/// The display destructor. This function should not be called as it is called automatically
		/// </summary>
		~Display();

		/// <summary>
		/// Updates the main game window and displays the colors of the current Buffer
		/// </summary>
		void Draw();

		/// <summary>
		/// <para>Prints to the console the contents of the Buffer.</para>
		/// Warning: This can take a long time on a big buffer so use sparinglly
		/// </summary>
		void PrintBuffer();

		/// <summary>
		/// Prints to the console the contents of the ColorPalette
		/// </summary>
		void PrintColorPalette();

		/// <summary>
		/// Updates the colors that are used when drawing the Buffer 
		/// </summary>
		void UpdateColors();

		/// <summary>
		/// Closes the main window
		/// </summary>
		void CloseWindow();

		/// <summary>
		/// Checks to see whether the main window should be closing
		/// </summary>
		/// <returns>A bool indicating the current closing status</returns>
		bool WindowShouldClose();

		/// <summary>
		/// </summary>
		/// <returns>The total size of the Buffer</returns>
		const size_t size() const;

		/// <summary>
		/// </summary>
		/// <returns>The X ( j ) size of the Buffer</returns>
		const size_t sizeX() const;

		/// <summary>
		/// </summary>
		/// <returns>The Y ( i ) size of the Buffer</returns>
		const size_t sizeY() const;


		/// <summary>
		/// Set the current Buffer offset in the main window (can be used to move the image around)
		/// </summary>
		/// <param name="Y_Offset"></param>
		/// <param name="X_Offset"></param>
		void SetOffsets(const float& Y_Offset, const float& X_Offset);
		
		/// <summary>
		/// This is the Buffer ( 2D array that holds all the indexes represating the colors of each "pixel" in the image )
		/// </summary>
		Hexxy::Data::array2D Buffer;

		/// <summary>
		/// This is the ColorPalette ( 1D array of RGB values to determine the colors of the image )
		/// </summary>
		Hexxy::Data::ColorPalette ColorPalette;

	private:
		void init();

	private:
		size_t Y, X;
		float m_Y_Offset, m_X_Offset;
	};
}