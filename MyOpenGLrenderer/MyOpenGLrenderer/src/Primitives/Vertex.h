#pragma once

#include "glm.hpp"

struct Vertex
{
public:
	Vertex()
		: Position(0.0f), Normal(0.0f), TexCoords(0.0f), Color(0.0f)
	{}

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec4 Color;
};