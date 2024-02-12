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
		virtual void OnRender(const Hexxy::Data::array2Dbase<uint8_t>& arrayData, const Hexxy::Data::ColorPaletteBase& colorPalette) {}
	};
}