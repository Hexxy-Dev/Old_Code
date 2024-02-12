#pragma once

#include "Settings.h"

#if SHOW_APP_CONSOLE == 0
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include "DataTypes.h"
#include "Utility.h"

#include "Core.h"
#include "Input.h"
#include "Audio.h"

namespace Hexxy
{
	template<size_t Y, size_t X, size_t colors>
	class Display
	{
	public:
		Display()
			: DisplaySizeY(Settings_Display_Height), DisplaySizeX(Settings_Display_Width)
		{ init(); }
		~Display()
		{
			Audio::StopSound();
			if (Scene)
			{
				Scene->~SceneBatchRendering();
				delete Scene;
				Scene = nullptr;
			}
			glfwDestroyWindow(window);
			Buffer.~array2D();
			ColorPalette.~ColorPalette();
			glfwTerminate();
		}

		void Draw()
		{ 
			Core::GL::windowRender(Scene, Buffer, ColorPalette);
		}

		void PrintBuffer() { Hexxy::Utility::printBuffer((Hexxy::Data::array2Dbase<uint8_t>&)Buffer); }
		void PrintColorPalette() { Hexxy::Utility::printColorPalette(ColorPalette); }

		void UpdateColors() 
		{ 
			ColorPalette.createPixelColors();
		}

		void CloseWindow()
		{
			Core::GL::CloseWindow();
		}

		const size_t size() const { return X * Y; }
		const size_t sizeX() const { return X; }
		const size_t sizeY() const { return Y; }

		Hexxy::Data::array2D<uint8_t, Y, X> Buffer;
		Hexxy::Data::ColorPalette<colors> ColorPalette;
	private:
		void init()
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
			Audio::init();

			Buffer.clear();

			int init = Core::GL::windowInit(DisplaySizeY, DisplaySizeX, "Le Window");
			if (init == -1)
			{
				throw("FATAL ERROR!!!");
			}
			else
			{
				Input::init(DisplaySizeY, DisplaySizeX, Y, X);

				glfwSetKeyCallback(window, ::key_callback);
				glfwSetCursorPosCallback(window, ::cursor_position_callback);
				glfwSetMouseButtonCallback(window, ::mouse_button_callback);
				glfwSetScrollCallback(window, ::scroll_callback);

				Input::On("ESCAPE", "PRESS", Core::GL::CloseWindow);

				Scene = new gameScene::SceneBatchRendering(Buffer, X * Y, DisplaySizeY, DisplaySizeX);
			}
		}

		gameScene::SceneBatchRendering* Scene;

		size_t DisplaySizeX, DisplaySizeY;
	};
}