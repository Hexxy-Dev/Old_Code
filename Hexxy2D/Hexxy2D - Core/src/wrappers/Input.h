#pragma once

/// <summary>
/// <para>Input namespace provides functions for easy interaction with the mouse and keyboard</para>
/// Also provides two variables: XMousePos, YMousePos whitch indicate the mouse position in grid coordinates
/// </summary>
namespace Input
{
	extern size_t XMousePos, YMousePos;

	/// <summary>
	/// <para>This function calls the provided function whenever the condition is met.</para>
	/// <para>WARNING: REPEAT should not be used to make wasd input as only one function can be called at a time.</para>
	/// If you want to make a wasd controller or have multiple keys pressed at once use IsPressed() instead.
	/// </summary>
	/// <param name="key">is the key you want to call the provided function</param>
	/// <param name="action">"PRESS", "RELEASE", "REPEAT"</param>
	/// <param name="function">the function to be called (function pointer with no params and void return type)</param>
	void On(const char* key, const char* action, void (*function)());

	/// <summary>
	/// <para>This function calls the provided function whenever the scroll wheel is turned.</para>
	/// <para>The function provides 2 variables: xoffset and yoffset.</para>
	/// yoffset is positive if the mouse wheel is turned up and negative if turned down
	/// </summary>
	/// <param name="function">the function to be called (function pointer with 2 doubles as input and void return type)</param>
	void OnScroll(void (*function)(double, double));

	/// <summary>
	/// <para>This function returnes a bool indicating weather the button is pressed</para>
	/// <para>This function keeps track of all pressed keys so multiple keys can be pressed at once</para>
	/// This function should be used if simultaneous input is required
	/// </summary>
	/// <param name="key">is the key you want to see if it is pressed</param>
	/// <returns>a bool indicating weather the key is pressed</returns>
	bool IsPressed(const char* key);
}

