#include "EBO.h"

EBO::EBO()
	:IndicesCount(0)
{
	glGenBuffers(1, &ID);
	bind();
}
EBO::~EBO()
{
	unbind();
	glDeleteBuffers(1, &ID);
}


void EBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void EBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void EBO::setDataStatic(const std::vector<unsigned int>& indices) const
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	IndicesCount = indices.size();
}

void EBO::setData(const std::vector<unsigned int>& indices) const
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);
	IndicesCount = indices.size();
}

void EBO::setSubData(const std::vector<unsigned int>& indices, const size_t& offset) const
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, sizeof(unsigned int) * indices.size(), indices.data());
	IndicesCount = indices.size();
}


