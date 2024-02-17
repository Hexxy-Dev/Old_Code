#include "GLFW/glfw3.h"
#include "GL/glew.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <iostream>

#include <future>
#include <Windows.h>
#include <atomic>

std::atomic_bool q = false;
std::atomic_bool w = false;
std::atomic_bool e = false;
std::atomic_bool wireframe = false;

float line_width = 1;


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		q = true;
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
		q = false;

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		w = true;
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		w = false;

	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		e = true;
	if (key == GLFW_KEY_E && action == GLFW_RELEASE)
		e = false;

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
		if (wireframe)
			wireframe = false;
		else
			wireframe = true;

	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
	{
		if (line_width < 10)
		{
			line_width++;
			glLineWidth(line_width);
		}
	}

	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
	{
		if (line_width > 1)
		{
			line_width--;
			glLineWidth(line_width);
		}
	}

}
void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

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
		: bottomLeft (x - 0.5f, y - 0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 0.8f),
		  bottomRight(x + 0.5f, y - 0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 0.8f),
		  topRight   (x + 0.5f, y + 0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 0.8f),
		  topLeft    (x - 0.5f, y + 0.5f, 0.0f,     0.0f, 1.0f, 1.0f, 0.8f)
	{}

	Quad(float x, float y, float z)
		: bottomLeft (x, y, z,    0.0f, 1.0f, 0.0f, 0.8f),
		  bottomRight(x, y, z,    0.0f, 0.0f, 1.0f, 0.8f),
		  topRight   (x, y, z,    1.0f, 0.0f, 0.0f, 0.8f),
		  topLeft    (x, y, z,    0.0f, 1.0f, 1.0f, 0.8f)
	{}

	Vertex bottomLeft;
	Vertex bottomRight;
	Vertex topRight;
	Vertex topLeft;
};

struct Cube
{
	Cube(float x, float y, float z, float scale, float transparency)
		:
		UPbottomLeft ((x - 0.5)* scale, (y + 0.5)* scale, (z - 0.5)* scale,     0.0f, 0.0f, 1.0f, transparency),
		UPbottomRight((x + 0.5)* scale, (y + 0.5)* scale, (z - 0.5)* scale,     0.0f, 0.0f, 1.0f, transparency),
		UPtopRight   ((x + 0.5)* scale, (y + 0.5)* scale, (z + 0.5)* scale,     0.0f, 0.0f, 1.0f, transparency),
		UPtopLeft    ((x - 0.5)* scale, (y + 0.5)* scale, (z + 0.5)* scale,     0.0f, 0.0f, 1.0f, transparency),
																								  
		LEFTbottomLeft ((x - 0.5)* scale, (y - 0.5)* scale, (z + 0.5)* scale,   1.0f, 0.0f, 1.0f, transparency),
		LEFTbottomRight((x - 0.5)* scale, (y - 0.5)* scale, (z - 0.5)* scale,   1.0f, 0.0f, 1.0f, transparency),
		LEFTtopRight   ((x - 0.5)* scale, (y + 0.5)* scale, (z - 0.5)* scale,   1.0f, 0.0f, 1.0f, transparency),
		LEFTtopLeft    ((x - 0.5)* scale, (y + 0.5)* scale, (z + 0.5)* scale,   1.0f, 0.0f, 1.0f, transparency),
																								  
		FRONTbottomLeft ((x - 0.5)* scale, (y - 0.5)* scale, (z - 0.5)* scale,  1.0f, 0.0f, 0.0f, transparency),
		FRONTbottomRight((x + 0.5)* scale, (y - 0.5)* scale, (z - 0.5)* scale,  1.0f, 0.0f, 0.0f, transparency),
		FRONTtopRight   ((x + 0.5)* scale, (y + 0.5)* scale, (z - 0.5)* scale,  1.0f, 0.0f, 0.0f, transparency),
		FRONTtopLeft    ((x - 0.5)* scale, (y + 0.5)* scale, (z - 0.5)* scale,  1.0f, 0.0f, 0.0f, transparency),
																								  
		RIGHTbottomLeft ((x + 0.5)* scale, (y - 0.5)* scale, (z - 0.5)* scale,  0.0f, 1.0f, 1.0f, transparency),
		RIGHTbottomRight((x + 0.5)* scale, (y - 0.5)* scale, (z + 0.5)* scale,  0.0f, 1.0f, 1.0f, transparency),
		RIGHTtopRight   ((x + 0.5)* scale, (y + 0.5)* scale, (z + 0.5)* scale,  0.0f, 1.0f, 1.0f, transparency),
		RIGHTtopLeft    ((x + 0.5)* scale, (y + 0.5)* scale, (z - 0.5)* scale,  0.0f, 1.0f, 1.0f, transparency),
																								  
		BACKbottomLeft ((x + 0.5)* scale, (y - 0.5)* scale, (z + 0.5)* scale,   1.0f, 1.0f, 0.0f, transparency),
		BACKbottomRight((x - 0.5)* scale, (y - 0.5)* scale, (z + 0.5)* scale,   1.0f, 1.0f, 0.0f, transparency),
		BACKtopRight   ((x - 0.5)* scale, (y + 0.5)* scale, (z + 0.5)* scale,   1.0f, 1.0f, 0.0f, transparency),
		BACKtopLeft    ((x + 0.5)* scale, (y + 0.5)* scale, (z + 0.5)* scale,   1.0f, 1.0f, 0.0f, transparency),
																								  
		DOWNbottomLeft ((x - 0.5)* scale, (y - 0.5)* scale, (z + 0.5)* scale,   0.0f, 1.0f, 0.0f, transparency),
		DOWNbottomRight((x + 0.5)* scale, (y - 0.5)* scale, (z + 0.5)* scale,   0.0f, 1.0f, 0.0f, transparency),
		DOWNtopRight   ((x + 0.5)* scale, (y - 0.5)* scale, (z - 0.5)* scale,   0.0f, 1.0f, 0.0f, transparency),
		DOWNtopLeft    ((x - 0.5)* scale, (y - 0.5)* scale, (z - 0.5)* scale,   0.0f, 1.0f, 0.0f, transparency)
	{}

	Vertex UPbottomLeft;
	Vertex UPbottomRight;
	Vertex UPtopRight;
	Vertex UPtopLeft;

	Vertex LEFTbottomLeft;
	Vertex LEFTbottomRight;
	Vertex LEFTtopRight;
	Vertex LEFTtopLeft;

	Vertex FRONTbottomLeft;
	Vertex FRONTbottomRight;
	Vertex FRONTtopRight;
	Vertex FRONTtopLeft;

	Vertex RIGHTbottomLeft;
	Vertex RIGHTbottomRight;
	Vertex RIGHTtopRight;
	Vertex RIGHTtopLeft;

	Vertex BACKbottomLeft;
	Vertex BACKbottomRight;
	Vertex BACKtopRight;
	Vertex BACKtopLeft;

	Vertex DOWNbottomLeft;
	Vertex DOWNbottomRight;
	Vertex DOWNtopRight;
	Vertex DOWNtopLeft;
};



std::atomic_bool stop = false;
std::atomic_bool go = true;

glm::mat4 model;

void fixed_update()
{
	go = false;
	if(q)
	model = glm::rotate(model, 0.0174533f, glm::vec3(0, 1, 0));
	if(w)
	model = glm::rotate(model, 0.0174533f, glm::vec3(0, 0, 1));
	if(e)
	model = glm::rotate(model, 0.0174533f, glm::vec3(1, 0, 0));
	go = true;
	return;
}

void Start()
{
	while (!stop)
	{
		fixed_update();
		Sleep(10);
	}
}

int window_width = 640;
int window_height = 480;

float FOV = 45.0f;
float perspective_near = 0.1f;
float perspective_far = 10.0f;


glm::vec3 camera_position(0.5f, 1.0f, 1.0f);
glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
glm::vec3 camera_up(0.0f, 1.0f, 0.0f);


int main()
{
	GLFWwindow* window;

	glfwInit();
	window = glfwCreateWindow(window_width, window_height, "3D WOOO", NULL, NULL);
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

	glEnable(GL_DEPTH_TEST);

	//glDepthMask(GL_FALSE);

	glDepthFunc(GL_LESS);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	Cube vertices[] =
	{
		Cube(0.0,0.0,0.0,0.5,1.0),
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
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec4 color;\n"
		"out vec4 Color;\n"
		"uniform mat4 mvp;\n"
		"void main()\n"
		"{\n"
		//"   gl_Position = vec4(position, 1.0);\n"
		"   gl_Position = mvp * vec4(position, 1.0);\n"
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


	model = glm::mat4(1.0f);
	/*
	glm::mat4 view = glm::lookAt(
		glm::vec3(0.5f, 1.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	//*///this is the same v as this ^
	glm::mat4 view = glm::lookAt(
		camera_position,
		camera_target,
		camera_up);

	glm::mat4 proj = glm::perspective(FOV, (float)window_width / (float)window_height, perspective_near, perspective_far);

	
	GLint uniMvp = glGetUniformLocation(Shader, "mvp");

	//mvp = glm::identity<glm::mat4>();

	double previousTime = glfwGetTime();
	int frameCount = 0;

	auto fi = std::async(std::launch::async, Start);

	while (!glfwWindowShouldClose(window))
	{
		if (go);

		if(wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - previousTime >= 1.0)
		{
			std::cout << frameCount << "\n";
			frameCount = 0;
			previousTime = currentTime;
		}

		//glClearColor(0xff, 0xff, 0xff, 0xff);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 mvp = proj * view * model;

		glUniformMatrix4fv(uniMvp, 1, GL_FALSE, glm::value_ptr(mvp));

		glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);

		if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	stop = true;

	delete indices;

	glfwTerminate();
	return 0;
}