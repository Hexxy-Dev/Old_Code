#include "Renderer.h"

#include "../../Profiler.h"

Renderer::Renderer(const std::string& vertex, const std::string& fragment)
	: Shader(vertex.c_str(), fragment.c_str()), Scene(nullptr)
{}

void Renderer::draw() const
{
	PROFILE_FUNCTION();
	Scene->Sort();

	glm::mat4 projection = Scene->Camera->createPerspective();
	glm::mat4 view = Scene->Camera->createViewMatrix();

	Shader.bind();

	Shader.setUniform3f("CameraPos", Scene->Camera->Transform.Position);

	Shader.setMat4("view", view);
	Shader.setMat4("projection", projection);

	if(Scene->ambientLight)
		SetLight("ambientLight", *Scene->ambientLight, glm::mat4(1.0f));

#define NR_POINT_LIGHTS 4
#define NR_DIRECTIONAL_LIGHTS 4
#define NR_SPOT_LIGHTS 4

	for (int i = 0; i < Scene->solidsSorted.size(); i++)
	{
		DrawObject(Scene->solidsSorted[i]);
	}
	for (int i = 0; i < Scene->transparentsSorted.size(); i++)
	{
		//printf("%f %f %f\n", Scene->transparentsSorted[i]->Transform.Position.x, Scene->transparentsSorted[i]->Transform.Position.y, Scene->transparentsSorted[i]->Transform.Position.z);
		DrawObject(Scene->transparentsSorted[i]);
	}
}

void Renderer::DrawObject(const Entity* entity) const
{
	PROFILE_FUNCTION();
	glm::mat4 model = entity->getModelMatrix();

	Shader.setMat4("model", model);

	Scene->CalculateClosestLights(entity);

	for (int i = 0; i < NR_POINT_LIGHTS && i < Scene->pointLightsSorted.size(); i++)
	{
		std::string destination = "pointLights[" + std::to_string(i) + "]";
		SetPointLight(destination, *Scene->pointLightsSorted[i]->pointLight, Scene->pointLightsSorted[i]->getModelMatrix());
	}

	for (int i = 0; i < NR_DIRECTIONAL_LIGHTS && i < Scene->directionalLights.size(); i++)
	{
		std::string destination = "directionalLights[" + std::to_string(i) + "]";
		SetDirectinalLight(destination, *Scene->directionalLights[i]->directionalLight, Scene->directionalLights[i]->getModelMatrix());
	}

	for (int i = 0; i < NR_SPOT_LIGHTS && i < Scene->spotLightsSorted.size(); i++)
	{
		std::string destination = "spotLights[" + std::to_string(i) + "]";
		SetSpotLight(destination, *Scene->spotLightsSorted[i]->spotLight, Scene->spotLightsSorted[i]->getModelMatrix());
	}
	entity->mesh->draw(Shader);
}

void Renderer::SetPointLight(const std::string& destination, const PointLight& pointLight, const glm::mat4& model) const
{
	PROFILE_FUNCTION();
	SetLight(destination + ".light", pointLight, model);
	Shader.setUniform1f(destination + ".quadratic", pointLight.quadratic);
	Shader.setUniform1f(destination + ".linear", pointLight.linear);
}

void Renderer::SetDirectinalLight(const std::string& destination, const DirectionalLight& directionalLight, const glm::mat4& model) const
{
	PROFILE_FUNCTION();
	SetLight(destination + ".light", directionalLight, model);
	Shader.setUniform3f(destination + ".direcLightDir", directionalLight.direcLightDir);
}

void Renderer::SetSpotLight(const std::string& destination, const SpotLight& spotLight, const glm::mat4& model) const
{
	PROFILE_FUNCTION();
	SetLight(destination + ".light", spotLight, model);
	Shader.setUniform1f(destination + ".outerCone", spotLight.outerCone);
	Shader.setUniform1f(destination + ".innerCone", spotLight.innerCone);
	Shader.setUniform3f(destination + ".spotLightDir", spotLight.spotLightDir);
}

void Renderer::SetLight(const std::string& destination, const Light& light, const glm::mat4& model) const
{
	PROFILE_FUNCTION();
	glm::vec3 lightPos = model * glm::vec4(light.lightPos, 1.0f);

	Shader.setUniform3f(destination + ".lightPos", lightPos);
	Shader.setUniform3f(destination + ".lightColor", light.lightColor);
	Shader.setUniform1f(destination + ".ambient", light.ambient);
	Shader.setUniform1f(destination + ".specularLight", light.specularLight);
	Shader.setUniform1i(destination + ".specPow", light.specPow);
}

//
//uniform PointLight pointLights[NR_POINT_LIGHTS];
//uniform DirectionalLight directionalLights[NR_DIRECTIONAL_LIGHTS];
//uniform SpotLight spotLights[NR_SPOT_LIGHTS];
//uniform Light ambientLight;
//
// struct Light {
//vec3 lightPos;
//vec3 lightColor;
//float ambient;
//float specularLight;
//int specPow;
//};
//struct PointLight {
//	Light light;
//	float quadratic;
//	float linear;
//};
//struct DirectionalLight {
//	Light light;
//	vec3 direcLightDir;
//};
//struct SpotLight {
//	Light light;
//	float outerCone;
//	float innerCone;
//	vec3 spotLightDir;
//};
//