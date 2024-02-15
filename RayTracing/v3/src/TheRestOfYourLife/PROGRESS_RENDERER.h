#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Globals.h"

#include <cstdio>

int window_Width = image_width;
int window_Height = image_height;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	window_Width = width;
	window_Height = height;
}

int PROGRESS_WINDOW_RENDER()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(window_Width, window_Height, "RayTracing", NULL, NULL);
	if (!window)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	glViewport(0, 0, window_Width, window_Height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//glfwSwapInterval(0);                                         ////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////

	float vertices[] = {
		-1.0f, -1.0f, 0.0f,     0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,     image_width, 0.0f,
		 1.0f,  1.0f, 0.0f,     image_width, image_height,
		-1.0f,  1.0f, 0.0f,     0.0f, image_height
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, indices, GL_STATIC_DRAW);

	const char* vertexSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 pos;\n"
		"layout (location = 1) in vec2 texCoord;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(pos, 1.0);\n"
		"	TexCoord = texCoord;\n"
		"}\0";

	const char* fragmentSource =
		"#version 330 core\n"
		"in vec2 TexCoord;\n"
		"out vec4 FragColor;\n"
		"uniform sampler2DRect Texture;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(Texture, TexCoord);\n"
		//"	FragColor = vec4(1.0,0.0,0.0,1.0);\n"
		"}\0";

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
	}

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
	}

	GLuint Shader;
	Shader = glCreateProgram();
	glAttachShader(Shader, vertexShader);
	glAttachShader(Shader, fragmentShader);
	glLinkProgram(Shader);
	glUseProgram(Shader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	////////////////////////////////////////////////////////////////////////////////
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_RECTANGLE, texture);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	////////////////////////////////////////////////////////////////////////////////
	glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	bool last_update = true;
	while (!glfwWindowShouldClose(window))
	{
		if (!PROGRESS_DONE)
			glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		else
			if (last_update)
			{
				glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
				last_update = false;
			}

		glClearColor(0xff, 0x00, 0x00, 0xff);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_RECTANGLE, texture);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteTextures(1, &texture);

	glfwDestroyWindow(window);
	glfwTerminate();
}