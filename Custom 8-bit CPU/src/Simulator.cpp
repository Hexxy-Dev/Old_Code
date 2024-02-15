#include "Simulator.h"
#include <functional>

std::vector<uint8_t> REG;
std::vector<uint8_t> RAM;
std::vector<uint8_t> ROM;

std::bitset<2> FLAGS;
enum FLAG {
	CARRY,
	SKIP
};

int Program_Counter;

std::unordered_map <uint8_t, std::function<void(uint8_t, uint8_t)>> Instruction_Set = {
	std::make_pair(0b00000000, [](uint8_t a, uint8_t b) {
	std::cout << "NOP\n";
	}), //nop
	std::make_pair(0b00111111, [](uint8_t a, uint8_t b) {
	Program_Counter = ROM.size();
	std::cout << "HLT\n";
	}), //hlt
	std::make_pair(0b10000001, [](uint8_t a, uint8_t b) {
		((b >= 0x10) ? RAM[b - 0x10] : REG[b]) = ((a >= 0x10) ? RAM[a - 0x10] : REG[a]);
	}), //mov
	std::make_pair(0b10000010, [](uint8_t a, uint8_t b) {
	REG[a] += REG[b];
	}), //add
	std::make_pair(0b10000011, [](uint8_t a, uint8_t b) {
	REG[a] -= REG[b];
	}), //sub
	std::make_pair(0b01000100, [](uint8_t a, uint8_t b) {
	std::cout << "0x" << std::hex << int(((a >= 0x10) ? RAM[a - 0x10] : REG[a])) << std::hex << '\n';
	}), //prn
	std::make_pair(0b01000101, [](uint8_t a, uint8_t b) {
	std::cout << ((a >= 0x10) ? RAM[a - 0x10] : REG[a]);
	}), //prc
	std::make_pair(0b01000110, [](uint8_t a, uint8_t b) {
		REG[a] = (!REG[a]);
	}), //not
	std::make_pair(0b10000111, [](uint8_t a, uint8_t b) {
		REG[a] = (REG[a] || REG[b]);
	}), //lor
	std::make_pair(0b10001000, [](uint8_t a, uint8_t b) {
		REG[a] = (REG[a] && REG[b]);
	}), //and
	std::make_pair(0b10001001, [](uint8_t a, uint8_t b) {
		REG[a] = REG[a] ^ REG[b];
	}), //xor
	std::make_pair(0b10001010, [](uint8_t a, uint8_t b) {
		REG[a] = REG[a] >> REG[b];
	}), //btr
	std::make_pair(0b10001011, [](uint8_t a, uint8_t b) {
		REG[a] = REG[a] << REG[b];
	}), //btl
	std::make_pair(0b10001100, [](uint8_t a, uint8_t b) {
		Program_Counter = REG[a] * 0xFF + REG[b] - 3;//why -3???
	}), //jmp
	std::make_pair(0b01001101, [](uint8_t a, uint8_t b) {
		if (REG[a])
			FLAGS[FLAG::SKIP] = true;
	}), //ifi
	std::make_pair(0b10001110, [](uint8_t a, uint8_t b) {
		REG[a] = (REG[a] == REG[b]);
	}), //eql
};










void Memory_Dump(const std::vector<uint8_t>& memory)
{
	for (auto val : memory)
		std::cout << std::bitset<8>(val) << ' ';
	std::cout << '\n' << std::hex;
	for (auto val : memory)
		std::cout << "0x" << (int)val << ' ';
	std::cout << std::hex << '\n';
}

void Simulate()
{
	FLAGS.set(FLAGS.size() - 1, false);
	REG.reserve(0x08);
	for (int i = 0; i < 0x08; i++)
		REG.emplace_back(0);
	RAM.reserve(0xFF - 0x10);
	for (int i = 0; i < 0xFF - 0x10; i++)
		RAM.emplace_back(0);

	std::ifstream Bytecode;
	int length = 0;
	Bytecode.open("./files/Bytecode.txt", std::ios::in | std::ios::binary);
	Bytecode.seekg(0, Bytecode.end);
	length = Bytecode.tellg();
	Bytecode.seekg(0, Bytecode.beg);
	char* buffer = new char[length];
	Bytecode.read(buffer, length);
	Bytecode.close();
	{	int i;
		for (i = 0; i < length - 1; i++)
			if (buffer[i] == 0x00 && buffer[i + 1] == 0x00)
				break;
			else
				RAM[i] = buffer[i];
		for (i += 2; i < length; i++)
			ROM.push_back(buffer[i]);
		if (ROM.capacity() > ROM.size())
			ROM.resize(ROM.size());
	}
	Memory_Dump(RAM);
	Memory_Dump(ROM);
	std::cout << "\n\n";

	for (; Program_Counter < ROM.size(); Program_Counter++) {
		if ((ROM[Program_Counter] >> 6) == 0b01) {
			if (!FLAGS[FLAG::SKIP])
				Instruction_Set[ROM[Program_Counter]](ROM[Program_Counter + 1], 0);
			else
				FLAGS[FLAG::SKIP] = false;
			Program_Counter++;
			continue;
		}
		if ((ROM[Program_Counter] >> 6) == 0b10) {
			if (!FLAGS[FLAG::SKIP])
				Instruction_Set[ROM[Program_Counter]](ROM[Program_Counter + 1], ROM[Program_Counter + 2]);
			else
				FLAGS[FLAG::SKIP] = false;
			Program_Counter += 2;
			continue;
		}
		if (!FLAGS[FLAG::SKIP])
			Instruction_Set[ROM[Program_Counter]](0, 0);
		else
			FLAGS[FLAG::SKIP] = false;
	}
}