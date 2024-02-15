#include "Assembler.h"

//#define ASM_SHOW_OUTPUT

std::unordered_map<std::string, uint8_t> Instruction_Set = {
	std::make_pair("nop", 0b00000000),
	std::make_pair("hlt", 0b00111111),
	std::make_pair("mov", 0b10000001),
	std::make_pair("add", 0b10000010),
	std::make_pair("sub", 0b10000011),
	std::make_pair("prn", 0b01000100),
	std::make_pair("prc", 0b01000101),
	std::make_pair("not", 0b01000110),
	std::make_pair("lor", 0b10000111),
	std::make_pair("and", 0b10001000),
	std::make_pair("xor", 0b10001001),
	std::make_pair("btr", 0b10001010),
	std::make_pair("btl", 0b10001011),
	std::make_pair("jmp", 0b10001100),
	std::make_pair("ifi", 0b01001101),
	std::make_pair("eql", 0b10001110),
};

void Assemble()
{
	std::ifstream Assembly;
	Assembly.open("./files/Assembly.txt");
	std::ofstream Bytecode;
	Bytecode.open("./files/Bytecode.txt", std::ios::out | std::ios::binary);
	std::string word;
#ifdef ASM_SHOW_OUTPUT
	std::cout << std::hex;
#endif
	while (Assembly >> word) {
		if (word[0] == '0') {
			char num = (word[2] - '0' - ((word[2] - '0' > 9) ? 7 : 0)) * 16 +
				(word[3] - '0' - ((word[3] - '0' > 9) ? 7 : 0));
			Bytecode << num;
#ifdef ASM_SHOW_OUTPUT
			std::cout << int(num) << ' ';
#endif
			continue;
		}
		if (Instruction_Set.find(word) == Instruction_Set.end()) {
			Bytecode << Instruction_Set["nop"];
			std::cout << "ASSEMBLER ERROR: OPCODE NOT FOUND";
			continue;
		}
		Bytecode << Instruction_Set[word];
#ifdef ASM_SHOW_OUTPUT
		std::cout << int(Instruction_Set[word]) << ' ';
#endif
	}
#ifdef ASM_SHOW_OUTPUT
	std::cout << std::hex << "\n\n";
#endif
	Assembly.close();
	Bytecode.close();
}