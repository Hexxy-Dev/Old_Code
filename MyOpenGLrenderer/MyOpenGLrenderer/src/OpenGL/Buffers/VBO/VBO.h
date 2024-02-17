#pragma once

#include "glad/glad.h"

#include "../../../Primitives/Vertex.h"

#include <vector>

class VBO {
public:
	VBO();
	~VBO();

	void bind() const;
	void unbind() const;
	
	void setDataStatic(const std::vector<Vertex>& vertices) const;
	void setData(const std::vector<Vertex>& vertices) const;
	void setSubData(const std::vector<Vertex>& vertices, const size_t& offset = 0) const;
	void mapBufferData(const std::vector<Vertex>& vertices) const;

private:
	GLuint ID;
private:
};