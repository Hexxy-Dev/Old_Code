#include "VAO.h"


VAO::VAO()
{
	glGenVertexArrays(1, &ID);
	bind();
}
VAO::~VAO()
{
	unbind();
	glDeleteVertexArrays(1, &ID);
}


void VAO::bind() const
{
	glBindVertexArray(ID);
}
void VAO::unbind() const
{
	glBindVertexArray(0);
}

void VAO::enableLayout(const GLuint& index) const
{
	glEnableVertexAttribArray(index);
}
void VAO::disableLayout(const GLuint& index) const
{
	glDisableVertexAttribArray(index);
}

void VAO::setLayout(const GLuint& index, const GLint& count, const GLuint& offset, const GLenum& type, const GLboolean& normalized) const
{
	glVertexAttribPointer(index, count, type, normalized, (GLsizei)sizeof(Vertex), (void*)offset);
}