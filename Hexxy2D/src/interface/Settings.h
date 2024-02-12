#pragma once

#include <cstdint>

////////////     Settings    ////////////

constexpr const char* Settings_Audio_Path = "res/audio/";

constexpr uint8_t Settings_Number_Of_Audio_Tracks = 6;

constexpr uint16_t Settings_Display_Height = 1080;

constexpr uint16_t Settings_Display_Width = 1920;

#define CORE_FULLSCREEN 1

#define SHOW_APP_CONSOLE 1

#define DoubleBuffered 1
#define VSync 1

//////////// End of settings ////////////

// these settings should only be edited BY HAND!
// do not attempt to edit them programatically

// Display size is in pixels
// the ratio between the display sizes and your display buffer sizes should be the same

// ABOUT INCLUDES:
// BECAUSE OF THE WAY I CREATED THIS LIBRARY, IF YOU INCLUDE Hexxy2D.h IN YOUR APP YOU WILL
// INCLUDE THE FOLLOWING STANDARD LIBRARIES AS WELL:
/*
	<cstdint>

	<cstring>
	<utility>

	<iostream>

	<string>
	<unordered_map>

	<vector>

	<memory>

	<future>
	<array>
	<atomic>
*/
// I SUGGEST YOU  STILL #include EVERYTHING YOU USE IN YOUR FILE EVEN IF IT IS IN THIS LIST ALREADY

// NOTES:

// YOU SHOULD USE
// sf::sleep(sf::milliseconds(300));
// OR
// sf::sleep(sf::seconds(1));
// BECAUSE IT SHOULD* BE BETTER THAN Sleep(1); FROM "windows.h"
// ALSO "windows.h" SHOULD BE AVOIDED AS IT IS USUALLY SLOW



// THINGS LEFT TO DO ???:
// ADD DOCUMENTATION ??? (Would be usefull but I'm too lazy rn )
// FIX INCLUDE THINGY ? (mabye if I decide to make it in a precompiled library)
// CLEAN UP CODE ? (ehh.. it's clean enough ... for now atleast)
// OPTIMISE CODE : REDUCE NUMBER OF HEAP ALLOCATIONS ?? (idk if it makes sense in the places that it is used)

// ACHIEVEMENT:
// ALMOAST COMPLETELY MEMORY-LEAK FREE ON FIRST TRY
// NOW, AS FAR AS I CAN SEE, THERE ARE NO MEMORY-LEAKS AT ALL