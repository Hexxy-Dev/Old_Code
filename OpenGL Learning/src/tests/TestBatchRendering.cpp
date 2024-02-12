#include "TestBatchRendering.h"


namespace test
{
	TestBatchRendering::TestBatchRendering()
		: m_Proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_translationA(glm::vec3(200, 200, 0))
	{
		///*
		float positions[] = {
			-150.0f, -50.0f,  0.18f, 0.6f, 0.96f, 1.0f,
			-50.0f,  -50.0f,  0.18f, 0.6f, 0.96f, 1.0f,
			-50.0f,   50.0f,  0.18f, 0.6f, 0.96f, 1.0f,
			-150.0f,  50.0f,  0.18f, 0.6f, 0.96f, 1.0f,

			 50.0f,  -50.0f,  1.0f, 0.83, 0.24, 1.0f,
			 150.0f, -50.0f,  1.0f, 0.83, 0.24, 1.0f,
			 150.0f,  50.0f,  1.0f, 0.83, 0.24, 1.0f,
			 50.0f,   50.0f,  1.0f, 0.83, 0.24, 1.0f,
		};//*/

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};
		
		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 2 * 6 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(4);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shaders/Batch.shader");
		m_Shader->Bind();
	}

	void TestBatchRendering::OnUpdate(float deltaTime)
	{}

	void TestBatchRendering::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			
			m_Shader->Bind();
			m_Shader->SetUniformMat4("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestBatchRendering::OnImGuiRender()
	{
		ImGui::SliderFloat("TranslationX", &m_translationA.x, 0.0f, 1920.0f);
		ImGui::SliderFloat("TranslationY", &m_translationA.y, 0.0f, 1080.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}