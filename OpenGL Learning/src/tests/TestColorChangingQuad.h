#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test
{
	class TestColorChangingQuad : public Test
	{
	public:
		TestColorChangingQuad();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_translationA;

		float m_R, m_G, m_B;
		float Rincrement, Gincrement, Bincrement;
		float m_RIncrement, m_GIncrement, m_BIncrement;
	};
}