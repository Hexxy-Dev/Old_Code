#pragma once

#include "glad/glad.h"

#include "../../../Primitives/Vertex.h"

class VAO {
public:
	VAO();
	~VAO();

	void bind() const;
	void unbind() const;

	void enableLayout(const GLuint& index) const;
	void disableLayout(const GLuint& index) const;
	void setLayout(const GLuint& index, const GLint& count, const GLuint& offset, const GLenum& type = GL_FLOAT, const GLboolean& normalized = GL_FALSE) const;

private:
	GLuint ID;
private:
};