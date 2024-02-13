#pragma once

#include "../tools.h"

#include <iostream>
#include <fstream>
#include <string>

#define RUN_PROC()															\
void Run()																	\
{																			\
std::string input;															\
std::ifstream fin;															\
fin.open(std::string("inputs/") + std::to_string(YEAR) + '/'				\
			+ std::to_string(DAY) + ".txt", std::ios::binary);				\
input.assign(std::istreambuf_iterator<char>(fin),							\
				std::istreambuf_iterator<char>());							\
fin.close();																\
std::cout << "Year " << YEAR << ":\n Day " << DAY << ":\n  Part 1:\n   ";	\
Part1(input);																\
std::cout << std::endl << "  Part 2:\n   ";									\
Part2(input);																\
std::cout << '\n' << std::endl;												\
}																			\
//

#define START namespace CAT_2(Y,YEAR) { namespace CAT_2(D,DAY) {
#define END RUN_PROC() } }


#include <unordered_map>
#include <regex>
#include <bitset>
#include <vector>
#include <wchar.h>