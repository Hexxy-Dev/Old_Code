#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "Renderer.h"

#include "DataTypes.h"

namespace gameScene
{
	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void OnUpdate() {}
		virtual void OnRender(float& Y_Offset, float& X_Offset, const Hexxy::Data::array2D& arrayData, const Hexxy::Data::ColorPalette& colorPalette) {}
	};
}