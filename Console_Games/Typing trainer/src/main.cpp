#include <iostream>
#include <limits>
#include <random>
#include <vector>
#include <chrono>
#include <conio.h>
#include <fstream>
#include <future>
#include "Win.h"

std::vector<char> Sessions[7][2] = {
	{{'a','s','d','f','j','k','l',';'},
	{'A','S','D','F','J','K','L',':'}},
	{{'a','s','d','f','g','h','j','k','l',';','\''},
	{'A','S','D','F','G','H','J','K','L',':','"'}},
	{{'q','w','e','r','t','y','u','i','o','p','[',']','\\'},
	{'Q','W','E','R','T','Y','U','I','O','P','{','}','|'}},
	{{'z','x','c','v','b','n','m',',','.','/'},
	{'Z','X','C','V','B','N','M','<','>','?'}},
	{{'1','2','3','4','5','6','7','8','9','0','-','='},
	{'!','@','#','$','%','^','&','*','(',')','_','+'}},
	{{}, {}},//placeholder for all of the above
	{{'4','5','6','7','8','9','1','2','3','0','.','+','-','*','/'},
	{}}//extended ascii maybe?
};

std::vector<std::string> Texts;

void Init()
{
	Sessions[5][0].reserve(100);
	for (size_t i = ' '; i <= '~'; i++)
		Sessions[5][0].emplace_back(i);
	Sessions[5][1] = Sessions[5][0];
	std::string name;
	std::ifstream fin("Texts.txt");
	while (fin >> name) Texts.push_back(name);
	fin.close();
}

class Settings {
public:
	static size_t m_Group_size;
	static bool m_Uppercase;
	static bool m_Mixed_case;
	static size_t m_Time_restraint;
	static size_t m_Accuracy_restraint;
	static size_t m_Characters_number;
	static bool m_Require_space;
	static bool m_Require_erase;
	static int m_Session;
	static bool m_Session_Text;

	static const char* CapitalLetters()
	{ return (m_Uppercase ? "On" : "Off"); }

	static const char* Mixed()
	{ return (m_Mixed_case ? "On" : "Off"); }

	static const char* RequireSpace()
	{ return (m_Require_space ? "On" : "Off"); }

	static const char* RequireErase()
	{ return (m_Require_erase ? "On" : "Off"); }
};
size_t Settings::m_Group_size = 3;
bool Settings::m_Uppercase = false;
bool Settings::m_Mixed_case = false;
size_t Settings::m_Time_restraint = 0;
size_t Settings::m_Accuracy_restraint = 0;
size_t Settings::m_Characters_number = 0;
bool Settings::m_Require_space = false;
bool Settings::m_Require_erase = false;
int Settings::m_Session = 0;
bool Settings::m_Session_Text = false;

std::string user_buffer;
std::vector<std::string> buffer;
float accuracy;

void Display()
{
	//ConsoleClear();
	//puts(".\n\n\n\n\n\n");
	//printf("\t\t\t       %.0f%%\n", accuracy);
	//printf("%s   %s   %s %s %s %s %s\n", user_buffer.c_str(),
	//	buffer[0].c_str(), buffer[1].c_str(), buffer[2].c_str(), buffer[3].c_str(),
	//	buffer[4].c_str(), buffer[5].c_str());
	//puts("\n\n\n\n\n\n\n\n\n");
	printf(".\n\n\n\n\n\n\t\t\t       %.0f%%\n%s   %s  %s %s %s\n\n\n\n\n\n\n\n\n\n",
		accuracy, user_buffer.c_str(), buffer[0].c_str(),
		buffer[1].c_str(), buffer[2].c_str(), buffer[3].c_str());
}

std::uniform_int_distribution<int> bin(0, 1);

void AddToBuffer(size_t k, std::mt19937& gen,
	std::uniform_int_distribution<int>& dist)
{
	char selected = ' ';
	if (Settings::m_Mixed_case)
		selected = Sessions[Settings::m_Session][bin(gen)][dist(gen)];
	else
		selected = Sessions[Settings::m_Session][Settings::m_Uppercase]
		[dist(gen)];
	buffer.push_back("");
	for (size_t i = 0; i < Settings::m_Group_size; i++)
		buffer[k] += selected;
}

void Start()
{
	user_buffer.clear();
	buffer.clear();
	size_t entered = 0;
	size_t correct = 0;

	for (size_t i = 0; i < 28; i++)
		user_buffer += "\033[00m \033[00m";

	std::random_device random_dev;
	std::mt19937 gen(random_dev());
	std::uniform_int_distribution<int> dist(0,
		(int)Sessions[Settings::m_Session][Settings::m_Uppercase].size() - 1);

	if(Settings::m_Session_Text) {
		std::uniform_int_distribution<int> distr(0, Texts.size() - 1);
		std::string tmp;
		std::ifstream fin(Texts[distr(gen)] + ".txt");
		while (fin >> tmp) buffer.push_back(tmp);
		fin.close();
	}
	else
		for (size_t k = 0; k < 4; k++)
			AddToBuffer(k, gen, dist);

	bool stop = false;
	auto start = std::chrono::high_resolution_clock::now();

	std::future<void> fi;
	if (Settings::m_Time_restraint)
		fi = std::async(std::launch::async, [&]() {
			while (!stop) {
				auto now = std::chrono::high_resolution_clock::now();
				auto elapsed =  now - start;
				float seconds = (double)elapsed.count() / 1000000000;
				if (seconds > Settings::m_Time_restraint)
					stop = true;
#define SKIP	_sleep(100);
#include "skip C4996.h"
			} });

	size_t words = 0;

	while (!stop) {
		size_t erase = 0;
		size_t current = 0;

		while (!stop) {
			if (!Settings::m_Session_Text)
				if(Settings::m_Characters_number)
					if (entered == Settings::m_Characters_number) {
						stop = true;
						break;
					}
			accuracy = ((float)correct / entered) * 100;
			Display();
			if(Settings::m_Accuracy_restraint)
				if (accuracy < Settings::m_Accuracy_restraint) {
					stop = true;
					break;
				}
			char c = _getch();
			if (c == '\x1b') { //esc
				stop = true;
				break;
			}
			if (c == '\b') {
				if (Settings::m_Require_erase)
					if (erase) {
						erase--;
						user_buffer.erase(user_buffer.size() - 11, user_buffer.size());
						user_buffer = "\033[00m \033[00m" + user_buffer;
					}
				continue;
			}

			entered++;
			user_buffer.erase(0, 11);
			
			if (current == buffer[0].size())
				if (Settings::m_Require_space || Settings::m_Session_Text)
					if (c == ' ' && !erase) {
						correct++;
						user_buffer += "\033[00m \033[00m";
						break;
					}
			if (buffer[0][current] == c && !erase) {
				correct++;
				user_buffer += "\033[00m";
				current++;
			} else {
				if (Settings::m_Require_erase)
					erase++;
				user_buffer += "\033[31m";//"\x1B[31m";
			}
			if (!Settings::m_Session_Text)
				if (current == buffer[0].size())
					if (!Settings::m_Require_space) {
						user_buffer += c;
						user_buffer += "\033[00m";
						break;
					}
			
			user_buffer += c;
			user_buffer += "\033[00m";
		}

		for (size_t i = 0; i < buffer.size() - 1; i++)
			buffer[i] = buffer[i + 1];
		buffer.pop_back();
		if (Settings::m_Session_Text) {
			if (buffer.size() < 4)
				buffer.push_back("");
			if (buffer[0] == "")
				break;
		} else
			AddToBuffer(buffer.size(), gen, dist);
		words++;
	}

	auto end = std::chrono::high_resolution_clock::now();
	ConsoleClear();
	auto duration = end - start; // nanoseconds
	float seconds = (double)duration.count() / 1000000000;
	float WPM = words / (seconds / 60);
	printf("Final stats:"
		"\n\tCharacters entered: %u"
		"\n\tAccuracy: %.2f"
		"\n\tTime: %.3f s"
		"\n\tWPM: %.2f\n",
		entered, accuracy, seconds, WPM);
#define SKIP _sleep(3500);
#include "skip C4996.h"
	//std::cin.sync();
	//std::cin.seekg(0, std::ios::end);
	//std::cin.clear();//idk why this doesn't work
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max());
	while (_kbhit()) _getch();
}

void Modifiers()
{
	ConsoleClear();
	printf("Sesion modifiers:"
		"\n\t0. Back"
		"\n\t1. Group size: %d"
		"\n\t2. Capital letters: %s"
		"\n\t3. Mixed cases: %s"
		"\n\t4. Time restraint: %d seconds (0 = infinite)"
		"\n\t5. Accuracy restraint: %d%"
		"\n\t6. Number of characters: %d (0 = infinite)"
		"\n\t7. Require space: %s"
		"\n\t8. Require erase: %s"
		"\n\t9. Start",
		Settings::m_Group_size, Settings::CapitalLetters(),
		Settings::Mixed(), Settings::m_Time_restraint,
		Settings::m_Accuracy_restraint, Settings::m_Characters_number,
		Settings::RequireSpace(), Settings::RequireErase());
	uint8_t option = _getch() - '0';
	ConsoleClear();
	switch (option) {
		case 0: return;
		case 1: {
			puts("Group size: (int)");
			std::cin >> Settings::m_Group_size;
			std::cin.get();
		} break;
		case 2: {
			puts("Enable capital leters?"
				"\n1. yes"
				"\n0. no");
			Settings::m_Uppercase = _getch() - '0';
		} break;
		case 3: {
			puts("Enable mixed cases?"
				"\n1. yes"
				"\n0. no");
			Settings::m_Mixed_case = _getch() - '0';
		} break;
		case 4: {
			puts("Time restraint: (int)");
			std::cin >> Settings::m_Time_restraint;
			std::cin.get();
		} break;
		case 5: {
			puts("Accuracy restraint: (int 0 - 100)");
			std::cin >> Settings::m_Accuracy_restraint;
			std::cin.get();
		} break;
		case 6: {
			puts("Number of characters: (int)");
			std::cin >> Settings::m_Characters_number;
			std::cin.get();
		} break;
		case 7: {
			puts("Require spaces?"
				"\n1. yes"
				"\n0. no");
			Settings::m_Require_space = _getch() - '0';
		} break;
		case 8: {
			puts("Require erase?"
				"\n1. yes"
				"\n0. no");
			Settings::m_Require_erase = _getch() - '0';
		} break;
		case 9: Start(); break;
	}
	Modifiers();
}

void ModifiersTextSession()
{
	ConsoleClear();
	printf("Sesion modifiers:"
		"\n\t0. Back"
		"\n\t1. Time restraint: %d seconds (0 = infinite)"
		"\n\t2. Accuracy restraint: %d%"
		"\n\t3. Require erase: %s"
		"\n\t9. Start",
		Settings::m_Time_restraint, Settings::m_Accuracy_restraint,
		Settings::RequireErase());
	uint8_t option = _getch() - '0';
	ConsoleClear();
	switch (option) {
		case 0: return;
		case 1: {
			puts("Time restraint: (int)");
			std::cin >> Settings::m_Time_restraint;
			std::cin.get();
		} break;
		case 2: {
			puts("Accuracy restraint: (int 0 - 100)");
			std::cin >> Settings::m_Accuracy_restraint;
			std::cin.get();
		} break;
		case 3: {
			puts("Require erase?"
				"\n1. yes"
				"\n0. no");
			Settings::m_Require_erase = _getch() - '0';
		} break;
		case 9: Start(); break;
	}
	ModifiersTextSession();
}

bool EXIT = false;

void Setup()
{
	ConsoleClear();
	puts("Please select a training session:"
		"\n\t0. EXIT"
		"\n\t1. Base keys"
		"\n\t2. Home row"
		"\n\t3. Top row"
		"\n\t4. Bottom row"
		"\n\t5. Numbers and special characters"
		"\n\t6. All of the above"
		"\n\t7. Numpad"
		"\n\t8. Actual text");
	char c = _getch() - '0';
	if (c > 0 && c < 8) {
		Settings::m_Session = c - 1;
		Modifiers();
	}
	if (c == 0) {
		EXIT = true;
		return;
	}
	if (c == 8) {
		Settings::m_Session_Text = true;
		ModifiersTextSession();
		Settings::m_Session_Text = false;
	}
}

int main()
{
	//printf("\n");
	//printf("\x1B[31mTexting\033[0m\t\t");
	//printf("\x1B[32mTexting\033[0m\t\t");
	//printf("\x1B[33mTexting\033[0m\t\t");
	//printf("\x1B[34mTexting\033[0m\t\t");
	//printf("\x1B[35mTexting\033[0m\n");
	//
	//printf("\x1B[36mTexting\033[0m\t\t");
	//printf("\x1B[36mTexting\033[0m\t\t");
	//printf("\x1B[36mTexting\033[0m\t\t");
	//printf("\x1B[37mTexting\033[0m\t\t");
	//printf("\x1B[93mTexting\033[0m\n");
	//
	//printf("\033[3;42;30mTexting\033[0m\t\t");
	//printf("\033[3;43;30mTexting\033[0m\t\t");
	//printf("\033[3;44;30mTexting\033[0m\t\t");
	//printf("\033[3;104;30mTexting\033[0m\t\t");
	//printf("\033[3;100;30mTexting\033[0m\n");
	//
	//printf("\033[3;47;35mTexting\033[0m\t\t");
	//printf("\033[2;47;35mTexting\033[0m\t\t");
	//printf("\033[1;47;35mTexting\033[0m\t\t");
	//printf("\t\t");
	//printf("\n");

	//for (char i = 0; i >= 0; i++)
	//	printf("%d: %c|\n", (int)i, i);

	AdjustConsole();
	FullScreen();

	Init();
	while (!EXIT)
		Setup();
}