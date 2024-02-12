#pragma once

#include "Scene.h"

#include "VertexBufferDynamic.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Vertex
{
	float x, y;
	unsigned int color;
	~Vertex() = default;
};

struct Quad
{
	Vertex vertices[4];
	void SetColor(unsigned int color)
	{
		for (char i = 0; i < 4; i++)
			vertices[i].color = std::move(color);
	}
	~Quad() = default;
};

namespace gameScene
{
	class SceneBatchRendering : public Scene
	{
	public:
		SceneBatchRendering(const Hexxy::Data::array2D& arrayData, const size_t& numQuads, const float& DisplaySizeY, const float& DisplaySizeX, const bool& QuadXScaling, const bool& QuadYScaling, const uint16_t& DefaultQuadSize);
		~SceneBatchRendering();

		void OnRender(float& Y_Offset, float& X_Offset, const Hexxy::Data::array2D& arrayData, const Hexxy::Data::ColorPalette& colorPalette) override;
	private:
		VertexArray* m_VAO;
		VertexBufferDynamic* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		Shader* m_Shader;

		glm::mat4 m_Proj, m_View, m_Model;
		size_t m_QuadSizeY, m_QuadSizeX, m_DisplaySizeY;
		uint32_t* indices;
		Quad* vertices;
	};
}