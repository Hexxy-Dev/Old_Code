#include "SceneBatchRendering.h"


namespace gameScene
{
	SceneBatchRendering::SceneBatchRendering(const Hexxy::Data::array2Dbase<uint8_t>& arrayData, const size_t& numQuads, const float& DisplaySizeY, const float& DisplaySizeX)
		: m_Proj(glm::ortho(0.0f, DisplaySizeX, 0.0f, DisplaySizeY, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Model(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_DisplaySizeY(DisplaySizeY)
	{
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

		m_QuadSize = DisplaySizeY / arrayData.sizeY();

		m_IndexBuffer = new IndexBuffer(indices, 6 * arrayData.size());

		m_VAO = new VertexArray();

		m_VertexBuffer = new VertexBufferDynamic(numQuads * sizeof(Quad));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(4);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = new Shader("res/shaders/Batch.shaders");
		m_Shader->Bind();
	}

	SceneBatchRendering::~SceneBatchRendering()
	{
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
		return;
	}

	Vertex CreateVertex(const size_t y, const size_t x, const Hexxy::Data::pixelColor& color)
	{
		Vertex vertex;

		vertex.x = x;
		vertex.y = y;
		vertex.r = color.R;
		vertex.g = color.G;
		vertex.b = color.B;
		vertex.a = color.A;

		return vertex;
	}

	Quad CreateQuad(const size_t DisplaySizeY, const size_t quadSize, const size_t i, const size_t j, const Hexxy::Data::pixelColor& color)
	{
		Quad quad;

		size_t x, y;

		y = DisplaySizeY - (i + 1) * quadSize ;
		x = j * quadSize;

		quad.vertices[0] = std::move(CreateVertex(y, x, color));
		quad.vertices[1] = std::move(CreateVertex(y + quadSize, x, color));
		quad.vertices[2] = std::move(CreateVertex(y + quadSize, x + quadSize, color));
		quad.vertices[3] = std::move(CreateVertex(y, x + quadSize, color));

		return quad;
	}

	void SceneBatchRendering::OnUpdate()
	{}

	void printQuad(Quad quad)
	{
		for(int i =0; i<4;i++)
			std::cout << quad.vertices[i].x << ", "
			<< quad.vertices[i].y << ", "
			<< quad.vertices[i].r << ",  "
			<< quad.vertices[i].g << ", "
			<< quad.vertices[i].b << ", "
			<< quad.vertices[i].a << "\n";

		std::cout << "\n";
	}

	void SceneBatchRendering::OnRender(const Hexxy::Data::array2Dbase<uint8_t>& arrayData, const Hexxy::Data::ColorPaletteBase& colorPalette)
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Quad* vertices = new Quad[arrayData.size()];

		for (size_t i = 0; i < arrayData.sizeY(); i++)
		{
			for (size_t j = 0; j < arrayData.sizeX(); j++)
			{
				vertices[i * arrayData.sizeX() + j] = std::move(CreateQuad(m_DisplaySizeY, m_QuadSize, i, j, colorPalette.getPixelColor(arrayData[i][j])));
			}
		}

		m_VertexBuffer->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, arrayData.size() * sizeof(Quad), vertices);

		Renderer renderer;
		{
			glm::mat4 mvp = m_Proj * m_View * m_Model;
			
			m_Shader->Bind();
			m_Shader->SetUniformMat4("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		delete[] vertices;
	}
}