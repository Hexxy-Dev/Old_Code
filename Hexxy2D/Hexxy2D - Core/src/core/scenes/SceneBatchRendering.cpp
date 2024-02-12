#include "SceneBatchRendering.h"

#include "ChromeProfiler.h"

namespace gameScene
{
	Vertex CreateVertex(const size_t y, const size_t x)
	{
#if PROFILING == 1
		PROFILE_FUNCTION();
#endif
		Vertex vertex;

		vertex.x = x;
		vertex.y = y;
		vertex.color = (0xff << 24) | (0x00 << 16) | (0x00 << 8) | (0x00);

		return vertex;
	}

	Quad CreateQuad(const size_t DisplaySizeY, const size_t quadSizeY, const size_t quadSizeX, const size_t i, const size_t j)
	{
#if PROFILING == 1
		PROFILE_FUNCTION();
#endif
		Quad quad;

		size_t x, y;

		y = DisplaySizeY - (i + 1) * quadSizeY; // add separate for X and Y
		x = j * quadSizeX;

		quad.vertices[0] = std::move(CreateVertex(y, x));
		quad.vertices[1] = std::move(CreateVertex(y + quadSizeY, x));
		quad.vertices[2] = std::move(CreateVertex(y + quadSizeY, x + quadSizeX));
		quad.vertices[3] = std::move(CreateVertex(y, x + quadSizeX));

		return quad;
	}

	SceneBatchRendering::SceneBatchRendering(const Hexxy::Data::array2D& arrayData, const size_t& numQuads, const float& DisplaySizeY, const float& DisplaySizeX, const bool& QuadXScaling, const bool& QuadYScaling, const uint16_t& DefaultQuadSize)
		: m_Proj(glm::ortho(0.0f, DisplaySizeX, 0.0f, DisplaySizeY, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Model(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_DisplaySizeY(DisplaySizeY)
	{
#if PROFILING == 1
		PROFILE_FUNCTION();
#endif
		indices = new uint32_t[6 * arrayData.size()];

		uint32_t k = 0;

		for (size_t i = 0; i < arrayData.size(); i++)
		{
			indices[i + k] = i * 4;
			indices[i + k + 1] = i * 4 + 1;
			indices[i + k + 2] = i * 4 + 2;
			indices[i + k + 3] = i * 4 + 2;
			indices[i + k + 4] = i * 4 + 3;
			indices[i + k + 5] = i * 4;
			k += 5;
		}
		//0, 1, 2, 2, 3, 0,
		//4, 5, 6, 6, 7, 4,

		if (QuadYScaling)
			m_QuadSizeY = DisplaySizeY / arrayData.sizeY();
		else
			m_QuadSizeY = DisplaySizeX / arrayData.sizeX();
		if (QuadXScaling)
			m_QuadSizeX = DisplaySizeX / arrayData.sizeX();
		else
			m_QuadSizeX = DisplaySizeY / arrayData.sizeY();
		

		if (!QuadYScaling && !QuadXScaling)
		{
			m_QuadSizeY = DefaultQuadSize;
			m_QuadSizeX = DefaultQuadSize;
		}

		m_IndexBuffer = new IndexBuffer(indices, 6 * arrayData.size());

		m_VAO = new VertexArray();

		m_VertexBuffer = new VertexBufferDynamic(numQuads * sizeof(Quad));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		//layout.Push<float>(4);
		layout.Push<unsigned char>(4);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = new Shader("res/shaders/Batch.shaders");
		m_Shader->Bind();


		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();


		vertices = new Quad[arrayData.size()];

		for (size_t i = 0; i < arrayData.sizeY(); i++)
		{
			for (size_t j = 0; j < arrayData.sizeX(); j++)
			{
				vertices[i * arrayData.sizeX() + j] = std::move(CreateQuad(m_DisplaySizeY, m_QuadSizeY, m_QuadSizeX, i, j));
			}
		}
	}

	SceneBatchRendering::~SceneBatchRendering()
	{
#if PROFILING == 1
		PROFILE_FUNCTION();
#endif
		if(indices)
			delete[] indices;
		indices = nullptr;
		delete m_VAO;
		m_VAO = nullptr;
		delete m_VertexBuffer;
		m_VertexBuffer = nullptr;
		delete m_IndexBuffer;
		m_IndexBuffer = nullptr;
		delete m_Shader;
		m_Shader = nullptr;

		delete[] vertices;
		return;
	}



	void SceneBatchRendering::OnRender(float& Y_Offset, float& X_Offset, const Hexxy::Data::array2D& arrayData, const Hexxy::Data::ColorPalette& colorPalette)
	{
#if PROFILING == 1
		PROFILE_FUNCTION();
#endif
		GLCall(glClearColor(colorPalette.m_ClearColor.R, colorPalette.m_ClearColor.G, colorPalette.m_ClearColor.B, colorPalette.m_ClearColor.A));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		for (size_t i = 0; i < arrayData.sizeY(); i++)
		{
			if (arrayData.updated[i])
			{
				arrayData.updated[i] = 0;
				for (size_t j = 0; j < arrayData.sizeX(); j++)
				{
					vertices[i * arrayData.sizeX() + j].SetColor(colorPalette[arrayData[i][j]].compressed);
				}
			}
		}

		//m_VertexBuffer->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, arrayData.size() * sizeof(Quad), vertices);

		Renderer renderer;
		{
			m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(X_Offset, Y_Offset, 0));

			glm::mat4 mvp = m_Proj * m_View * m_Model;
			
			//m_Shader->Bind();
			m_Shader->SetUniformMat4("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}
}