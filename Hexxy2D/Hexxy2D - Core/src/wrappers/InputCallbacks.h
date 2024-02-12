#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Input
{
	void init(size_t DisplaySizeY, size_t DisplaySizeX, size_t GridY, size_t GridX);

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
}