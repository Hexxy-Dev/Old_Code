#pragma once

#include "TestsInterface.h"

#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <sstream>

#include "WindowsAbstraction.h"



#define FAIL 0x4e
#define PASS 0x2e
#define NORMAL 0x0f
#define CASE_FAIL 0x04
#define CASE_PASS 0x02

#define CONSOLE_COLOR(X) SetTextColor(X)


#define COUT_PRINTING

#ifdef COUT_PRINTING
std::string Print_Buffer;
#define ADD_ENDL(X) (X + "\n")
#define PRINT_BUFFER() std::cout.write(Print_Buffer.data(), Print_Buffer.size())
#define PRINT(X) Print_Buffer = ADD_ENDL(X);  PRINT_BUFFER()
#else
#define PRINT(X) puts((X).c_str())
#endif // COUT_PRINTING



struct Test
{
	Test(const std::string& name, const size_t tests, bool (*func)())
		: name(name), number_of_tests(tests), run(func)
	{}
	std::string name;
	size_t number_of_tests;
	bool (*run)();
};

std::vector<Test> Tests;



#define TEST_BLOCK(NAME) char NAME##_TEST_BLOCK = []{
#define TEST_BLOCK_END return '0'; }();


#define TEST_BEGIN(NAME,TESTS) []{																	\
	Tests.push_back(Test(#NAME,TESTS,[]{															\
		size_t correct, tests;																		\
		for(tests = 0, correct = 0; tests < TESTS; tests++) {										\
			PRINT("\tRunning Test " + std::to_string(tests + 1) + " of " + std::to_string(TESTS));	\
//

#define TEST_END(RESULT,EXPECTED)														\
			if(RESULT == EXPECTED) { correct++; CONSOLE_COLOR(CASE_PASS); }				\
			else CONSOLE_COLOR(CASE_FAIL);												\
			std::cout << "\t\tResult: " << RESULT << " Expected: " << EXPECTED << '\n';	\
			CONSOLE_COLOR(NORMAL);														\
		}																				\
	return (correct == tests);															\
	}));																				\
}();																					\
//

void Custom_Tests::Run()
{
	InitWindowsAbstractionLayer();
	srand(time(NULL));
	for (auto& Test : Tests) {
		PRINT("Running " + std::to_string(Test.number_of_tests) + " " + Test.name + " Tests...");
		if (!Test.run()) {
			CONSOLE_COLOR(FAIL);
			PRINT(Test.name + " Test Failed!!");
		}
		else {
			CONSOLE_COLOR(PASS);
			PRINT(Test.name + " Test Passed!!");
		}
		CONSOLE_COLOR(NORMAL);
	}
}

// INTERESTING TIMING MECHANISM:
//clock_t start = clock();
//clock_t ticks = clock() - start;
//std::cout << (double)ticks / CLOCKS_PER_SEC << "\n";