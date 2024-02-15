#include "Compiler.h"


struct Reg {
	Reg(std::string name)
		: Name(name), Value(0)
	{}
	std::string Name;
	uint8_t Value;
};

struct Label {
	Label(std::string name)
		: Name(name), adress1(0), adress2(0)
	{}
	std::string Name;
	uint8_t adress1;
	uint8_t adress2;
};

void Compile()
{
	std::ifstream Code;
	Code.open("./files/Code.txt");

	std::string word;
	std::string lastReg;

	std::vector<Reg> registers;
	std::vector<Label> labels;

	while (Code >> word) {
		if (word[0] == '#') {
			std::string label = "";
			for (int i = 1; i < word.size(); i++)
				label += word[i];
			labels.push_back(label);
		}
		if (word == "ui8") {
			std::string RegName;
			Code >> RegName;
			registers.push_back(RegName);
			lastReg = RegName;
		}
		if (word == "=") {
			uint8_t value;
			Code >> value;
			for(uint8_t i = 0; i < registers.size(); i++)
				if (registers[i].Name == lastReg) {
					registers[i].Value = value;
					break;
				}
		}
	}
	Code.close();

	//std::ofstream Assembly;
	//Assembly.open("./files/Assembly.txt", std::ios::out);
	//
	//Assembly.close();
}