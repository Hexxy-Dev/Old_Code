#pragma once

#include "glad/glad.h"

#include <vector>

class EBO {
public:
	EBO();
	~EBO();

	void bind() const;
	void unbind() const;


	void setDataStatic(const std::vector<unsigned int>& indices) const;
	void setData(const std::vector<unsigned int>& indices) const;
	void setSubData(const std::vector<unsigned int>& indices, const size_t& offset = 0) const;

	mutable size_t IndicesCount;
private:
	GLuint ID;
private:
};