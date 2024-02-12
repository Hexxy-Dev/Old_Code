#pragma once

#include "Scene.h"

#include "VertexBufferDynamic.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace gameScene
{
	class SceneBatchRendering : public Scene
	{
	public:
		SceneBatchRendering(const Hexxy::Data::array2Dbase<uint8_t>& arrayData, const size_t& numQuads, const float& DisplaySizeY, const float& DisplaySizeX);
		~SceneBatchRendering();

		void OnUpdate() override;
		void OnRender(const Hexxy::Data::array2Dbase<uint8_t>& arrayData, const Hexxy::Data::ColorPaletteBase& colorPalette) override;
	private:
		VertexArray* m_VAO;
		VertexBufferDynamic* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		Shader* m_Shader;

		glm::mat4 m_Proj, m_View, m_Model;
		size_t m_QuadSize, m_DisplaySizeY;
		uint32_t* indices;
	};
}