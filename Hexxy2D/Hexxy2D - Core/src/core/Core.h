#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "SceneBatchRendering.h"

#include "DataTypes.h"

extern GLFWwindow* window;

namespace Core
{
	namespace GL
	{
		int windowInit(uint16_t sizeX, uint16_t sizeY, const char* name);

		void windowRender(float& Y_Offset, float& X_Offset, gameScene::Scene* currentScene, const Hexxy::Data::array2D& arrayData, const Hexxy::Data::ColorPalette& colorPalette);

		void CloseWindow();
	}
}