#include "Hexxy2D.h"

#if SHOW_APP_CONSOLE == 0
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include "Utility.h"

#include "Core.h"
#include "InputCallbacks.h"

#include "SFML/Audio.hpp"

#include <future>
//#include <atomic>

#include "ChromeProfiler.h"

gameScene::SceneBatchRendering* Scene;

std::atomic_bool Stop_Fixed_Update = false;

void FixedUpdate(void (*function)())
{
#if PROFILING == 1
	PROFILE_FUNCTION();
#endif

	while (!Stop_Fixed_Update)
	{
		function();
		sf::sleep(sf::milliseconds(Settings_Fixed_Update_Rate));
		Hexxy::Fixed_Update_OK = true;
	}

	std::cout << "Fixed Update Stopped!!\n";
	return;
}
std::future<void> FixedUpdatePtr;

namespace Hexxy
{
	std::atomic_bool Fixed_Update_OK = true;

	void Set_Fixed_Update_Function(void (*function)())
	{ FixedUpdatePtr = std::async(std::launch::async, FixedUpdate, function); }

	void Wait_Fixed_Update()
	{
		if(!Fixed_Update_OK)
			sf::sleep(sf::milliseconds(1));
	}

	void Sleep_For_Seconds(const size_t& seconds)
	{ sf::sleep(sf::seconds(seconds)); }

	void Sleep_For_Milliseconds(const size_t& milliseconds)
	{ sf::sleep(sf::milliseconds(milliseconds)); }

	Display::~Display()
	{
#if PROFILING == 1
		PROFILE_FUNCTION();
#endif

		Stop_Fixed_Update = true;
		sf::sleep(sf::milliseconds(Settings_Fixed_Update_Rate));
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

#if PROFILING == 1 || PROFILING == 2
		Instrumentor::Instance().endSession();
#endif
	}

	void Display::Draw() 
	{
#if PROFILING == 1
		PROFILE_FUNCTION();
#endif
		Core::GL::windowRender(m_Y_Offset, m_X_Offset, Scene, Buffer, ColorPalette); 
	}

	void Display::PrintBuffer() { Hexxy::Utility::printBuffer((Hexxy::Data::array2D&)Buffer); }
	void Display::PrintColorPalette() { Hexxy::Utility::printColorPalette(ColorPalette); }

	void Display::UpdateColors() { Buffer.UpdateAll(); ColorPalette.CreateCompressedColor(); }

	void Display::CloseWindow() { Core::GL::CloseWindow(); }

	bool Display::WindowShouldClose() { return glfwWindowShouldClose(window); }

	const size_t Display::size() const { return X * Y; }
	const size_t Display::sizeX() const { return X; }
	const size_t Display::sizeY() const { return Y; }

	void Display::SetOffsets(const float& Y_Offset, const float& X_Offset)
	{
		m_Y_Offset = Y_Offset;
		m_X_Offset = X_Offset;
	}

	void Display::init()
	{
#if PROFILING == 1 || PROFILING == 2
		Instrumentor::Instance().beginSession("Profile");
#endif
#if PROFILING == 1
		PROFILE_FUNCTION();
#endif

		Buffer.clear();

#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
		Audio::init();

		int init = Core::GL::windowInit(Settings_Display_Height, Settings_Display_Width, Settngs_Window_Name);
		if (init == -1)
		{
			throw("FATAL ERROR!!!");
		}
		else
		{
			Input::init(Settings_Display_Height, Settings_Display_Width, Y, X);

			glfwSetKeyCallback(window, Input::key_callback);
			glfwSetCursorPosCallback(window, Input::cursor_position_callback);
			glfwSetMouseButtonCallback(window, Input::mouse_button_callback);
			glfwSetScrollCallback(window, Input::scroll_callback);

			Input::On("ESCAPE", "PRESS", Core::GL::CloseWindow);

			Scene = new gameScene::SceneBatchRendering(Buffer, X * Y, Settings_Display_Height, Settings_Display_Width, Settings_Do_Quad_Scaling_On_X, Settings_Do_Quad_Scaling_On_Y, Settings_Default_Quad_Size);
		}
	}
}