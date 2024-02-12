#include "TestColorChangingQuad.h"


namespace test
{
	TestColorChangingQuad::TestColorChangingQuad()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_translationA(200, 200, 0), m_R(0.0f), m_G(0.0f), m_B(0.0f),
		m_RIncrement(0.05f), m_GIncrement(0.03f), m_BIncrement(0.07f)
	{
		float positions[] = {
		 -150.0f, -150.0f, 0.0f, 0.0f,
		  150.0f, -150.0f, 1.0f, 0.0f,
		  150.0f,  150.0f, 1.0f, 1.0f,
		 -150.0f,  150.0f, 0.0f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		
		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
	}

	void TestColorChangingQuad::OnUpdate(float deltaTime)
	{
		if (m_R > 1.0f)
			Rincrement = -m_RIncrement;
		else if (m_R <= 0.0f)
			Rincrement = m_RIncrement;
		m_R += Rincrement;

		if (m_G > 1.0f)
			Gincrement = -m_GIncrement;
		else if (m_G <= 0.0f)
			Gincrement = m_GIncrement;
		m_G += Gincrement;

		if (m_B > 1.0f)
			Bincrement = -m_BIncrement;
		else if (m_B <= 0.0f)
			Bincrement = m_BIncrement;
		m_B += Bincrement;
	}

	void TestColorChangingQuad::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			
			m_Shader->Bind();
			m_Shader->SetUniformMat4("u_MVP", mvp);

			m_Shader->SetUniform4f("u_Color", m_R, m_G, m_B, 1.0f);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestColorChangingQuad::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_translationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat("R Speed", &m_RIncrement, 0.0f, 0.5f);
		ImGui::SliderFloat("G Speed", &m_GIncrement, 0.0f, 0.5f);
		ImGui::SliderFloat("B Speed", &m_BIncrement, 0.0f, 0.5f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}