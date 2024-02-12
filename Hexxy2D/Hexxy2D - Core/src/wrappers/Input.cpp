#include "Input.h"
#include "InputCallbacks.h"

#include "Settings.h"

#include <map>
#include <unordered_map>
#include <array>
#include <bitset>


//////////////////////////////////////////////// TODO: change map to enum

std::unordered_map<uint16_t, uint8_t> keys =
{
std::make_pair(GLFW_KEY_SPACE,          0),
std::make_pair(GLFW_KEY_APOSTROPHE,     1),
std::make_pair(GLFW_KEY_COMMA,          2),
std::make_pair(GLFW_KEY_MINUS,          3),
std::make_pair(GLFW_KEY_PERIOD,         4),
std::make_pair(GLFW_KEY_SLASH,          5),
std::make_pair(GLFW_KEY_0,              6),
std::make_pair(GLFW_KEY_1,              7),
std::make_pair(GLFW_KEY_2,              8),
std::make_pair(GLFW_KEY_3,              9),
std::make_pair(GLFW_KEY_4,              10),
std::make_pair(GLFW_KEY_5,              11),
std::make_pair(GLFW_KEY_6,              12),
std::make_pair(GLFW_KEY_7,              13),
std::make_pair(GLFW_KEY_8,              14),
std::make_pair(GLFW_KEY_9,              15),
std::make_pair(GLFW_KEY_SEMICOLON,      16),
std::make_pair(GLFW_KEY_EQUAL,          17),
std::make_pair(GLFW_KEY_A,              18),
std::make_pair(GLFW_KEY_B,              19),
std::make_pair(GLFW_KEY_C,              20),
std::make_pair(GLFW_KEY_D,              21),
std::make_pair(GLFW_KEY_E,              22),
std::make_pair(GLFW_KEY_F,              23),
std::make_pair(GLFW_KEY_G,              24),
std::make_pair(GLFW_KEY_H,              25),
std::make_pair(GLFW_KEY_I,              26),
std::make_pair(GLFW_KEY_J,              27),
std::make_pair(GLFW_KEY_K,              28),
std::make_pair(GLFW_KEY_L,              29),
std::make_pair(GLFW_KEY_M,              30),
std::make_pair(GLFW_KEY_N,              31),
std::make_pair(GLFW_KEY_O,              32),
std::make_pair(GLFW_KEY_P,              33),
std::make_pair(GLFW_KEY_Q,              34),
std::make_pair(GLFW_KEY_R,              35),
std::make_pair(GLFW_KEY_S,              36),
std::make_pair(GLFW_KEY_T,              37),
std::make_pair(GLFW_KEY_U,              38),
std::make_pair(GLFW_KEY_V,              39),
std::make_pair(GLFW_KEY_W,              40),
std::make_pair(GLFW_KEY_X,              41),
std::make_pair(GLFW_KEY_Y,              42),
std::make_pair(GLFW_KEY_Z,              43),
std::make_pair(GLFW_KEY_LEFT_BRACKET,   44),
std::make_pair(GLFW_KEY_BACKSLASH,      45),
std::make_pair(GLFW_KEY_RIGHT_BRACKET,  46),
std::make_pair(GLFW_KEY_GRAVE_ACCENT,   47),
std::make_pair(GLFW_KEY_ESCAPE,         48),
std::make_pair(GLFW_KEY_ENTER,          49),
std::make_pair(GLFW_KEY_TAB,            50),
std::make_pair(GLFW_KEY_BACKSPACE,      51),
std::make_pair(GLFW_KEY_INSERT,         52),
std::make_pair(GLFW_KEY_DELETE,         53),
std::make_pair(GLFW_KEY_RIGHT,          54),
std::make_pair(GLFW_KEY_LEFT,           55),
std::make_pair(GLFW_KEY_DOWN,           56),
std::make_pair(GLFW_KEY_UP,             57),
std::make_pair(GLFW_KEY_PAGE_UP,        58),
std::make_pair(GLFW_KEY_PAGE_DOWN,      59),
std::make_pair(GLFW_KEY_HOME,           60),
std::make_pair(GLFW_KEY_END,            61),
std::make_pair(GLFW_KEY_CAPS_LOCK,      62),
std::make_pair(GLFW_KEY_SCROLL_LOCK,    63),
std::make_pair(GLFW_KEY_NUM_LOCK,       64),
std::make_pair(GLFW_KEY_PRINT_SCREEN,   65),
std::make_pair(GLFW_KEY_PAUSE,          66),
std::make_pair(GLFW_KEY_F1,             67),
std::make_pair(GLFW_KEY_F2,             68),
std::make_pair(GLFW_KEY_F3,             69),
std::make_pair(GLFW_KEY_F4,             70),
std::make_pair(GLFW_KEY_F5,             71),
std::make_pair(GLFW_KEY_F6,             72),
std::make_pair(GLFW_KEY_F7,             73),
std::make_pair(GLFW_KEY_F8,             74),
std::make_pair(GLFW_KEY_F9,             75),
std::make_pair(GLFW_KEY_F10,            76),
std::make_pair(GLFW_KEY_F11,            77),
std::make_pair(GLFW_KEY_F12,            78),
std::make_pair(GLFW_KEY_F13,            79),
std::make_pair(GLFW_KEY_F14,            80),
std::make_pair(GLFW_KEY_F15,            81),
std::make_pair(GLFW_KEY_F16,            82),
std::make_pair(GLFW_KEY_F17,            83),
std::make_pair(GLFW_KEY_F18,            84),
std::make_pair(GLFW_KEY_F19,            85),
std::make_pair(GLFW_KEY_F20,            86),
std::make_pair(GLFW_KEY_F21,            87),
std::make_pair(GLFW_KEY_F22,            88),
std::make_pair(GLFW_KEY_F23,            89),
std::make_pair(GLFW_KEY_F24,            90),
std::make_pair(GLFW_KEY_F25,            91),
std::make_pair(GLFW_KEY_KP_0,           92),
std::make_pair(GLFW_KEY_KP_1,           93),
std::make_pair(GLFW_KEY_KP_2,           94),
std::make_pair(GLFW_KEY_KP_3,           95),
std::make_pair(GLFW_KEY_KP_4,           96),
std::make_pair(GLFW_KEY_KP_5,           97),
std::make_pair(GLFW_KEY_KP_6,           98),
std::make_pair(GLFW_KEY_KP_7,           99),
std::make_pair(GLFW_KEY_KP_8,           100),
std::make_pair(GLFW_KEY_KP_9,           101),
std::make_pair(GLFW_KEY_KP_DECIMAL,     102),
std::make_pair(GLFW_KEY_KP_DIVIDE,      103),
std::make_pair(GLFW_KEY_KP_MULTIPLY,    104),
std::make_pair(GLFW_KEY_KP_SUBTRACT,    105),
std::make_pair(GLFW_KEY_KP_ADD,         106),
std::make_pair(GLFW_KEY_KP_ENTER,       107),
std::make_pair(GLFW_KEY_KP_EQUAL,       108),
std::make_pair(GLFW_KEY_LEFT_SHIFT,     109),
std::make_pair(GLFW_KEY_LEFT_CONTROL,   110),
std::make_pair(GLFW_KEY_LEFT_ALT,       111),
std::make_pair(GLFW_KEY_LEFT_SUPER,     112),
std::make_pair(GLFW_KEY_RIGHT_SHIFT,    113),
std::make_pair(GLFW_KEY_RIGHT_CONTROL,  114),
std::make_pair(GLFW_KEY_RIGHT_ALT,      115),
std::make_pair(GLFW_KEY_RIGHT_SUPER,    116),
std::make_pair(GLFW_KEY_MENU,           117),
std::make_pair(GLFW_MOUSE_BUTTON_RIGHT, 118),
std::make_pair(GLFW_MOUSE_BUTTON_LEFT,  119),
std::make_pair(GLFW_MOUSE_BUTTON_MIDDLE,120),
std::make_pair(GLFW_MOUSE_BUTTON_4,     121),
std::make_pair(GLFW_MOUSE_BUTTON_5,     122),
std::make_pair(GLFW_MOUSE_BUTTON_6,     123),
std::make_pair(GLFW_MOUSE_BUTTON_7,     124),
std::make_pair(GLFW_MOUSE_BUTTON_8,     125),
};

std::unordered_map<const char*, uint8_t> keysOrder =
{
std::make_pair("SPACE",        0),
std::make_pair("APOSTROPHE",   1),
std::make_pair("COMMA",        2),
std::make_pair("MINUS",        3),
std::make_pair("PERIOD",       4),
std::make_pair("SLASH",        5),
std::make_pair("0",            6),
std::make_pair("1",            7),
std::make_pair("2",            8),
std::make_pair("3",            9),
std::make_pair("4",            10),
std::make_pair("5",            11),
std::make_pair("6",            12),
std::make_pair("7",            13),
std::make_pair("8",            14),
std::make_pair("9",            15),
std::make_pair("SEMICOLON",    16),
std::make_pair("EQUAL",        17),
std::make_pair("A",            18),
std::make_pair("B",            19),
std::make_pair("C",            20),
std::make_pair("D",            21),
std::make_pair("E",            22),
std::make_pair("F",            23),
std::make_pair("G",            24),
std::make_pair("H",            25),
std::make_pair("I",            26),
std::make_pair("J",            27),
std::make_pair("K",            28),
std::make_pair("L",            29),
std::make_pair("M",            30),
std::make_pair("N",            31),
std::make_pair("O",            32),
std::make_pair("P",            33),
std::make_pair("Q",            34),
std::make_pair("R",            35),
std::make_pair("S",            36),
std::make_pair("T",            37),
std::make_pair("U",            38),
std::make_pair("V",            39),
std::make_pair("W",            40),
std::make_pair("X",            41),
std::make_pair("Y",            42),
std::make_pair("Z",            43),
std::make_pair("LEFT_BRACKET", 44),
std::make_pair("BACKSLASH",    45),
std::make_pair("RIGHT_BRACKET",46),
std::make_pair("GRAVE_ACCENT", 47),
std::make_pair("ESCAPE",       48),
std::make_pair("ENTER",        49),
std::make_pair("TAB",          50),
std::make_pair("BACKSPACE",    51),
std::make_pair("INSERT",       52),
std::make_pair("DELETE",       53),
std::make_pair("RIGHT",        54),
std::make_pair("LEFT",         55),
std::make_pair("DOWN",         56),
std::make_pair("UP",           57),
std::make_pair("PAGE_UP",      58),
std::make_pair("PAGE_DOWN",    59),
std::make_pair("HOME",         60),
std::make_pair("END",          61),
std::make_pair("CAPS_LOCK",    62),
std::make_pair("SCROLL_LOCK",  63),
std::make_pair("NUM_LOCK",     64),
std::make_pair("PRINT_SCREEN", 65),
std::make_pair("PAUSE",        66),
std::make_pair("F1",           67),
std::make_pair("F2",           68),
std::make_pair("F3",           69),
std::make_pair("F4",           70),
std::make_pair("F5",           71),
std::make_pair("F6",           72),
std::make_pair("F7",           73),
std::make_pair("F8",           74),
std::make_pair("F9",           75),
std::make_pair("F10",          76),
std::make_pair("F11",          77),
std::make_pair("F12",          78),
std::make_pair("F13",          79),
std::make_pair("F14",          80),
std::make_pair("F15",          81),
std::make_pair("F16",          82),
std::make_pair("F17",          83),
std::make_pair("F18",          84),
std::make_pair("F19",          85),
std::make_pair("F20",          86),
std::make_pair("F21",          87),
std::make_pair("F22",          88),
std::make_pair("F23",          89),
std::make_pair("F24",          90),
std::make_pair("F25",          91),
std::make_pair("KP_0",         92),
std::make_pair("KP_1",         93),
std::make_pair("KP_2",         94),
std::make_pair("KP_3",         95),
std::make_pair("KP_4",         96),
std::make_pair("KP_5",         97),
std::make_pair("KP_6",         98),
std::make_pair("KP_7",         99),
std::make_pair("KP_8",         100),
std::make_pair("KP_9",         101),
std::make_pair("KP_DECIMAL",   102),
std::make_pair("KP_DIVIDE",    103),
std::make_pair("KP_MULTIPLY",  104),
std::make_pair("KP_SUBTRACT",  105),
std::make_pair("KP_ADD",       106),
std::make_pair("KP_ENTER",     107),
std::make_pair("KP_EQUAL",     108),
std::make_pair("LEFT_SHIFT",   109),
std::make_pair("LEFT_CONTROL", 110),
std::make_pair("LEFT_ALT",     111),
std::make_pair("LEFT_SUPER",   112),
std::make_pair("RIGHT_SHIFT",  113),
std::make_pair("RIGHT_CONTROL",114),
std::make_pair("RIGHT_ALT",    115),
std::make_pair("RIGHT_SUPER",  116),
std::make_pair("MENU",         117),
std::make_pair("RIGHT_MOUSE",  118),
std::make_pair("LEFT_MOUSE",   119),
std::make_pair("MIDDLE_MOUSE", 120),
std::make_pair("MOUSE_4", 121),
std::make_pair("MOUSE_5", 122),
std::make_pair("MOUSE_6", 123),
std::make_pair("MOUSE_7", 124),
std::make_pair("MOUSE_8", 125),
};

std::map<uint16_t, uint8_t> actions =
{
std::make_pair(GLFW_RELEASE, 0),
std::make_pair(GLFW_PRESS,   1),
std::make_pair(GLFW_REPEAT,  2)
};

std::unordered_map<const char*, uint8_t> actionsOrder =
{
std::make_pair("RELEASE", 0),
std::make_pair("PRESS",   1),
std::make_pair("REPEAT",  2)
};


void nothing() {}
void nothingScroll(double xoffset, double yoffset) {}

std::array<void (*)(), 126 * 3> pointers;

std::bitset<126> pressedKeys;

void (*scrollPointer)(double, double);

size_t QuadSizeX, QuadSizeY;

namespace Input
{
	size_t XMousePos, YMousePos;

	void init(size_t DisplaySizeY, size_t DisplaySizeX, size_t GridY, size_t GridX)
	{
		if (Settings_Do_Quad_Scaling_On_Y)
			QuadSizeY = DisplaySizeY / GridY;
		else
			QuadSizeY = DisplaySizeX / GridX;
		if (Settings_Do_Quad_Scaling_On_X)
			QuadSizeX = DisplaySizeX / GridX;
		else
			QuadSizeX = DisplaySizeY / GridY;

		if (!Settings_Do_Quad_Scaling_On_Y && !Settings_Do_Quad_Scaling_On_X)
		{
			QuadSizeY = Settings_Default_Quad_Size;
			QuadSizeX = Settings_Default_Quad_Size;
		}
		pointers.fill(nothing);
		scrollPointer = nothingScroll;
	}

	void On(const char* key, const char* action, void (*function)())
	{
		pointers[size_t(keysOrder[key]) * 3 + actionsOrder[action]] = function;
	}

	void OnScroll(void (*function)(double, double)) { scrollPointer = function; }

	bool IsPressed(const char* key) { return pressedKeys[keysOrder[key]]; }



	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		pointers[size_t(keys[key]) * 3 + actions[action]]();

		if (action == GLFW_PRESS)
			pressedKeys[keys[key]] = 1;

		if (action == GLFW_RELEASE)
			pressedKeys[keys[key]] = 0;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		pointers[size_t(keys[button]) * 3 + actions[action]]();

		if (action == GLFW_PRESS)
			pressedKeys[keys[button]] = 1;

		if (action == GLFW_RELEASE)
			pressedKeys[keys[button]] = 0;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Input::XMousePos = xpos / QuadSizeX;
		Input::YMousePos = ypos / QuadSizeY;
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		scrollPointer(xoffset, yoffset);
	}
}