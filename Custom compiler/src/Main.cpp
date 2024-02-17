#include "Commons.h"
#include "Compiler.h"
#include "Interpreter.h"

int main()
{
InternalVariableReset();
	Input = "x = x + 3 - 2 - (5 - 4)\n";
	Init();
	Compiler::C1::Assignment();
	//Compiler::C1::Expression();
	if (Look != '\n')
		Expected("Newline");


puts("\n--------------------");
InternalVariableReset();

	Input = "?x \n ?b \n y = x * b \n !y .";
	Input = "x = 5 \n b = 3 \n y = x * b \n !y .";
	Init();
	Interpreter::InitTable();
	while (Look != '.') {
		switch (Look) {
			case '?': Interpreter::Input(); break;
			case '!': Interpreter::Output(); break;
			default: Interpreter::Assignment(); break;
		}
		NewLine();
	}


puts("\n--------------------");
InternalVariableReset();

	Input = "afi=bece";
	Init();
	Compiler::C2::DoProgram();


puts("\n--------------------");
InternalVariableReset();

	Input = "(3+5)=8&F";
	Init();
	Compiler::C3::BoolExpression();


puts("\n--------------------");
InternalVariableReset();

	Input = "ia=bxlye";
	Init();
	Compiler::C4::DoProgram();

	std::cin.get();std::cin.get();
}