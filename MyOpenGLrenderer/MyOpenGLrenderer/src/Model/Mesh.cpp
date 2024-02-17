#include "Mesh.h"

#include "../Profiler.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const bool& transparent, const bool& wireframe)
	: VBO(), VAO(), EBO(), is_Transparent(transparent), is_Wireframe(wireframe)
{
	this->vertices = vertices;
	this->indices = indices;

	if (!BaseTexture)
		createBaseTexture();

	setupMesh();
}

void Mesh::createBaseTexture()
{
	PROFILE_FUNCTION();
	glGenTextures(1, &BaseTexture);
	glBindTexture(GL_TEXTURE_2D, BaseTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLubyte image[1][1][4];
	image[0][0][0] = (GLubyte)255;
	image[0][0][1] = (GLubyte)255;
	image[0][0][2] = (GLubyte)255;
	image[0][0][3] = (GLubyte)255;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
}

void Mesh::updateData()
{
	PROFILE_FUNCTION();
	VBO.bind();
	VBO.setDataStatic(vertices);
}

void Mesh::draw(const Shader& Shader)
{
	PROFILE_FUNCTION();
	VBO.bind();
	VAO.bind();
	EBO.bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BaseTexture);

	if (textures.size())
	{
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			Shader.setUniform1i(textures[i].name, i);
			glBindTexture(GL_TEXTURE_2D, textures[i].ID);
		}
		glDrawElements(GL_TRIANGLES, EBO.IndicesCount, GL_UNSIGNED_INT, (GLsizei)0);
	}
	else
	{
		if (is_Wireframe)
		{
			glDrawElements(GL_LINES, EBO.IndicesCount, GL_UNSIGNED_INT, (GLsizei)0);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, EBO.IndicesCount, GL_UNSIGNED_INT, (GLsizei)0);
		}
	}

}



void Mesh::setupMesh()
{
	PROFILE_FUNCTION();
	VBO.bind();
	VBO.setDataStatic(vertices);

	VAO.bind();
	VAO.setLayout(0, 3, offsetof(Vertex, Position));
	VAO.setLayout(1, 3, offsetof(Vertex, Normal));
	VAO.setLayout(2, 2, offsetof(Vertex, TexCoords));
	VAO.setLayout(3, 4, offsetof(Vertex, Color));
	VAO.enableLayout(0);
	VAO.enableLayout(1);
	VAO.enableLayout(2);
	VAO.enableLayout(3);

	EBO.bind();
	EBO.setDataStatic(indices);
}