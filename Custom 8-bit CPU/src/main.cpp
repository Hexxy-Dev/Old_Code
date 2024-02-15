#include "Commons.h"
#include "Simulator.h"
#include "Assembler.h"
#include "Compiler.h"

int main()
{
	puts("Available Tools:\n1. Simulator\n2. Assembler\n3. Compiler\n");
	char option = std::cin.get();
	switch (option)
	{
	case '1':
		Simulate();
		break;
	case '2':
		Assemble();
		break;
	case '3':
		Compile();
		break;
	default:
		Compile();
		Assemble();
		Simulate();
		break;
	}
	std::cin.get();
	std::cin.get();
}