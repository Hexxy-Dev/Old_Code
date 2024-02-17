#include "VBO.h"


VBO::VBO()
{
	glGenBuffers(1, &ID);
	bind();
}
VBO::~VBO()
{
	unbind();
	glDeleteBuffers(1, &ID);
}


void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void VBO::setDataStatic(const std::vector<Vertex>& vertices) const
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

void VBO::setData(const std::vector<Vertex>& vertices) const
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
}

void VBO::setSubData(const std::vector<Vertex>& vertices, const size_t& offset) const
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Vertex) * vertices.size(), vertices.data());
}

void VBO::mapBufferData(const std::vector<Vertex>& vertices) const
{

}