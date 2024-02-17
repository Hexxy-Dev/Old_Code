#include "GLFW/glfw3.h"
#include "GL/glew.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <iostream>

#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

bool q = false;
bool w = false;
bool e = false;
bool wireframe = false;

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

struct Vertex {
	glm::vec3 Position;
	glm::vec4 Color;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	{
		this->vertices = vertices;
		this->indices = indices;

		setupMesh();
	}

	void Draw()
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

private:
	unsigned int VAO, VBO, EBO;

	void setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex colors
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

		glBindVertexArray(0);
	}
};

Mesh* CreateSphere(float radius, int sectorCount, int stackCount)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	float x, y, z, xy;

	float sectorStep = 2 * M_PI / sectorCount;
	float stackStep = M_PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

			Vertex vertex;
			vertex.Position.x = x;
			vertex.Position.y = y;
			vertex.Position.z = z;

			vertex.Color.r = 0.1f;
			vertex.Color.g = 0.5f;
			vertex.Color.b = 0.5f;
			vertex.Color.a = 1.0f;

			vertices.push_back(vertex);
		}
	}

	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	return new Mesh(vertices, indices);
}

glm::mat4 model;

void fixed_update()
{
	
	return;
}

//int window_width = 640;
//int window_height = 480;

int window_width = 1920;
int window_height = 1080;

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

	glm::mat4 view = glm::lookAt(
		camera_position,
		camera_target,
		camera_up);

	glm::mat4 proj = glm::perspective(FOV, (float)window_width / (float)window_height, perspective_near, perspective_far);

	
	GLint uniMvp = glGetUniformLocation(Shader, "mvp");

	double previousTime = glfwGetTime();
	int frameCount = 0;

	bool fixed_update_bool = false;

	Mesh* mesh = CreateSphere(0.5f, 36, 18);

	while (!glfwWindowShouldClose(window))
	{
		if(wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		double currentTime = glfwGetTime();
		float deltaTime = currentTime - previousTime;
		frameCount++;
		if (deltaTime >= 1.0)
		{
			std::cout << frameCount << "\n";
			frameCount = 0;
			previousTime = currentTime;

			fixed_update_bool = false;
		}

		if (deltaTime >= 0.2 && !fixed_update_bool)
		{
			fixed_update_bool = true;

			fixed_update();
		}

		if (q)
			model = glm::rotate(model, 0.0174533f * deltaTime / 10, glm::vec3(0, 1, 0));
		if (w)
			model = glm::rotate(model, 0.0174533f * deltaTime / 10, glm::vec3(0, 0, 1));
		if (e)
			model = glm::rotate(model, 0.0174533f * deltaTime / 10, glm::vec3(1, 0, 0));


		//glClearColor(0xff, 0xff, 0xff, 0xff);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 mvp = proj * view * model;

		glUniformMatrix4fv(uniMvp, 1, GL_FALSE, glm::value_ptr(mvp));

		mesh->Draw();

		if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}