#pragma once

#include "../Primitives/Vertex.h"
#include "../Primitives/Texture.h"

#include "../OpenGL/Buffers/VBO/VBO.h"
#include "../OpenGL/Buffers/VAO/VAO.h"
#include "../OpenGL/Buffers/EBO/EBO.h"
#include "../OpenGL/Shader/Shader.h"

#include <vector>

static GLuint BaseTexture;

class Mesh {
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const bool& transparent = false, const bool& wireframe = false);

	void createBaseTexture();

	void updateData();

	void draw(const Shader& Shader);


	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	bool is_Transparent;
	bool is_Wireframe;
private:
	VBO VBO;
	VAO VAO;
	EBO EBO;
private:
	void setupMesh();
};