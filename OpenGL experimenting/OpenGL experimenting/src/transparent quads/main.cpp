#include "GLFW/glfw3.h"
#include "GL/glew.h"

#include "glm.hpp"

#include <iostream>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	GLFWwindow* window;

	glfwInit();
	window = glfwCreateWindow(640, 480, "3D WOOO", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwWindowHint(GL_VERSION, 3.3);
	glfwSwapInterval(0);
	glewInit();

	glfwSetKeyCallback(window, keyCallback);
	glfwSetFramebufferSizeCallback(window, resizeCallback);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	struct Vertex
	{
		Vertex(float x, float y, float z, float r, float g, float b, float a)
			: x(x), y(y), z(z), r(r), g(g), b(b), a(a)
		{}

		float x;
		float y;
		float z;

		float r;
		float g;
		float b;
		float a;
	};

	struct Quad
	{
		Quad(float x, float y)
			: bottomLeft (x - 0.5f, y - 0.5f, 0.0f,    0.0f, 1.0f, 0.0f, 0.8f),
			  bottomRight(x + 0.5f, y - 0.5f, 0.0f,    0.0f, 0.0f, 1.0f, 0.8f),
			  topRight   (x + 0.5f, y + 0.5f, 0.0f,    1.0f, 0.0f, 0.0f, 0.8f),
			  topLeft    (x - 0.5f, y + 0.5f, 0.0f,    0.0f, 1.0f, 1.0f, 0.8f)
		{}

		Vertex bottomLeft;
		Vertex bottomRight;
		Vertex topRight;
		Vertex topLeft;
	};

	Quad vertices[] =
	{
		Quad(0,0),
		Quad(0.5f,0.5f),
		Quad(-0.5f,-0.5f)
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	uint32_t* indices;

	int quad_count = sizeof(vertices) / sizeof(Quad);
	int indices_count = quad_count * 6;
	indices = new uint32_t[indices_count];

	int k = 0;
	for (int i = 0; i < quad_count; i++)
	{
		indices[k + 0] = 0 + i * 4;
		indices[k + 1] = 1 + i * 4;
		indices[k + 2] = 2 + i * 4;
		indices[k + 3] = 2 + i * 4;
		indices[k + 4] = 3 + i * 4;
		indices[k + 5] = 0 + i * 4;
		k += 6;
	}

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices_count, indices, GL_STATIC_DRAW);

	const char* vertexSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 pos;\n"
		"layout (location = 1) in vec4 color;\n"
		"out vec4 Color;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
		"	Color = color;\n"
		"}\0";

	const char* fragmentSource =
		"#version 330 core\n"
		"in vec4 Color;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = Color;\n"
		"}\0";

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//get compilation status
	if (!success)
	{
		// get info
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//get compilation status
	if (!success)
	{
		// get info
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint Shader;
	Shader = glCreateProgram();
	glAttachShader(Shader, vertexShader);
	glAttachShader(Shader, fragmentShader);
	glLinkProgram(Shader);
	glUseProgram(Shader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0xff, 0xff, 0xff, 0xff);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete indices;

	glfwTerminate();
	return 0;
}