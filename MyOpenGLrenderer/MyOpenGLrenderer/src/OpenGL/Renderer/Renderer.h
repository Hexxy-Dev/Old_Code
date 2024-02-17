#pragma once

#include "glm.hpp"

#include "../../Scene/Scene.h"

class Renderer {
public:

	Renderer(const std::string& vertex, const std::string& fragment);

	void draw() const;

	Scene* Scene;
private:
	Shader Shader;
private:
	void DrawObject(const Entity* entity) const;

	void SetPointLight(const std::string& destination, const PointLight& pointLight, const glm::mat4& model) const;
	void SetDirectinalLight(const std::string& destination, const DirectionalLight& directionalLight, const glm::mat4& model) const;
	void SetSpotLight(const std::string& destination, const SpotLight& spotLight, const glm::mat4& model) const;
	void SetLight(const std::string& destination, const Light& light, const glm::mat4& model) const;
};