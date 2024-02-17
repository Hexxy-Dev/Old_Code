#pragma once

#include "glm.hpp"

struct Light {
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	float ambient = 0.20f;
	float specularLight = 0.50f;
	int specPow = 8;
};


struct PointLight : public Light {
	float quadratic = 1.0;
	float linear = 0.7;
};


struct DirectionalLight : public Light {
	glm::vec3 direcLightDir = glm::vec3(1.0f, 1.0f, 0.0f);
};


struct SpotLight : public Light {
	float outerCone = 0.90f; // cos(angle)
	float innerCone = 0.95f;
	glm::vec3 spotLightDir = glm::vec3(0.0f, -1.0f, 0.0f);
};