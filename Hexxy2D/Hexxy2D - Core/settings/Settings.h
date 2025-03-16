#pragma once

#include <cstdint>

////////////     Settings    ////////////

constexpr const char* Settings_Window_Name = "Le Window";

constexpr const char* Settings_Audio_Path = "res/audio/";

constexpr uint8_t Settings_Number_Of_Audio_Tracks = 6;

constexpr uint16_t Settings_Display_Height = 1080;

constexpr uint16_t Settings_Display_Width = 1920;

const bool Settings_Do_Quad_Scaling_On_X = false;
const bool Settings_Do_Quad_Scaling_On_Y = true;

const uint16_t Settings_Default_Quad_Size = 1;

constexpr uint16_t Settings_Fixed_Update_Rate = 20;


#ifdef _DEBUG // setting in debug mode
	#define CORE_FULLSCREEN 0

	#define SHOW_APP_CONSOLE 1
	#define SHOW_FPS 1

	#define VSync 0

#else // settings in release mode
	#define CORE_FULLSCREEN 1

	#define SHOW_APP_CONSOLE 0
	#define SHOW_FPS 0

	#define VSync 0
#endif // _DEBUG


// change to 1 for full profiling (profiling for some engine functions like draw and init
// as well as your functions)
// chage to 2 to profile only the functions you want (no game engine functions)
// WARNING: FILE SIZE GETS BIG QUICK (results.json in the main solution folder)
#define PROFILING 0
#define PROFILING_FULL_NAME 0

/* ADD THIS TO EVERY FUNCTION YOU WANT TO PROFILE
#if PROFILING == 1 || PROFILING == 2
	PROFILE_FUNCTION();
#endif
*/

// TO VIEW THE DATA GO TO: chrome://tracing/  ON CHROME AND DRAG AND DROP THE results.json FILE
//////////// End of settings ////////////

// these settings should only be edited BY HAND!
// do not attempt to edit them programatically

// Display size is in pixels
// the ratio between the display sizes and your display buffer sizes should be the same

// Settings_Do_Quad_Scaling_On_X = false; and Settings_Do_Quad_Scaling_On_Y = true; can be used for side scrollers :)

// Settings_Default_Quad_Size is the quad size in pixels when bothj scaling methods are off

// Settings_Do_Quad_Scaling_On_X = false; and Settings_Do_Quad_Scaling_On_Y = false; can be used for top down games

// CORE_FULLSCREEN is here mostlly for debugging purposes because mouse input and graphics get wonky in windowed mode
// The games created with this lib should be played in fullscreen

// SHOW_APP_CONSOLE this applies for the .exe file and if set to 0 will not start a console at all so it is more like
// a proper finished game

// DoubleBuffered is a graphics option and has 2 buffers to prevent screen tearing
// If DoubleBuffered is disabled the game will try to run at fastest fps it can and will ignore VSync settings

// VSync caps the framerate at your monitor's framerate to prevent screen tearing
// If VSync is disabled the game will try to run at fastest fps it can
// For some reason VSync seems to really tank performance in debug mode (mabye in release as well)

// Settings_Fixed_Update_Rate (in milliseconds) sets the frequency of fixed updates

// YOU SHOULD USE
// Hexxy::Sleep_For_Milliseconds(300);
// OR
// Hexxy::Sleep_For_Seconds(1);
// BECAUSE IT SHOULD* BE BETTER THAN Sleep(1); FROM "windows.h"
// ALSO "windows.h" SHOULD BE AVOIDED AS IT IS USUALLY SLOW


// ABOUT INCLUDES:
// BECAUSE OF THE WAY I CREATED THIS LIBRARY, IF YOU INCLUDE Hexxy2D.h IN YOUR APP YOU WILL
// INCLUDE THE FOLLOWING STANDARD LIBRARIES AS WELL:
/*
	<cstdint>

	<cstring>
	<utility>

	--------- // should be till here ??

	<iostream>

	<string>
	<unordered_map>

	<vector>

	<memory>

	<future>
	<array>
	<atomic>
*/