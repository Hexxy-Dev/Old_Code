#include "Commons.h"

#include "WindowsAbstraction.h"

// The order of the characters is my interpretation of multiple frequency charts
std::string Ascii = "etao inshrdlcumwfgypbvkjxqzETAOINSHRDLCUMWFGYP,.BVK\"'-?JX;!QZ:10)*(2`3954876/_[]=\n\r>~<#&{}^|\\@%$\t+";

//template<typename T>
//struct PrintableCharMap {
//	static const uint8_t Printable_char_nr = '~' - ' ' + 2 + 3;
//	T* m_values;
//	PrintableCharMap()
//		: m_values(new T[Printable_char_nr])
//	{
//		for (uint8_t i = 0; i < Printable_char_nr; i++)
//			m_values[i] = nullptr;
//	}
//	~PrintableCharMap() { delete[] m_values; }
//	T& operator[](char c) // "Hashing function" XD
//	{
//		switch (c) {
//			case '\n': return m_values[Printable_char_nr - 1];
//			case '\r': return m_values[Printable_char_nr - 2];
//			case '\t': return m_values[Printable_char_nr - 3];
//		}
//		return m_values[c - ' '];
//	}
//};
//
//template<typename T>
//struct LetterEntry {
//	LetterEntry(T code) : m_Code(code), m_Next() {}
//	~LetterEntry()
//	{
//		for (uint8_t i = 0; i < m_Next.Printable_char_nr; i++)
//			if (m_Next.m_values[i])
//				delete m_Next.m_values[i];
//	}
//	T m_Code;
//	PrintableCharMap<LetterEntry<T>*> m_Next;
//};
//
//template<typename T>
//PrintableCharMap<LetterEntry<T>*>* CreateDictionary(size_t& code)
//{
//	PrintableCharMap<LetterEntry<T>*>* Dictionary = new PrintableCharMap<LetterEntry<T>*>();
//
//	for (size_t i = 0; i < Ascii.size(); i++)
//		(*Dictionary)[Ascii[i]] = new LetterEntry<T>(code++);
//
//	return Dictionary;
//}
//
struct BitStream {
	std::vector<bool> m_bitData;

	template<typename T>
	void EMIT(T value, size_t bitsNr) {
		//std::vector<bool> bits;
		//bits.reserve(bitsNr);
		//for (size_t i = 0; i < bitsNr; i++)
		//	bits.emplace_back(value & (1 << i));
		//m_bitData.reserve(bits.size());
		//for (size_t i = 0; i < bits.size(); i++)
		//	m_bitData.emplace_back(bits[i]);

		m_bitData.reserve(bitsNr);
		for (int64_t i = bitsNr - 1; i >= 0; i--)
			m_bitData.push_back(value & ((uint64_t)1 << i)); // writing bits backwards
	}

	std::string CREATE_STRING()
	{
		std::string output;
		uint8_t byte = 0;
		uint8_t bitsWritten = 0;
		for (size_t i = 0; i < m_bitData.size(); i++)
			if (bitsWritten == 8) {
				output += byte;
				byte = 0;
				bitsWritten = 0;
				i--;
			}
			else {
				bitsWritten++;
				byte <<= 1;
				byte |= m_bitData[i];
			}
		char padding = 0;
		if (bitsWritten) {
			while (bitsWritten != 8) {
				padding++;
				bitsWritten++;
				byte <<= 1;
			}
			output += byte;
		}
		output += padding;	// add a char to the end of output
							// to represent padding of last byte

		return output;
	}
};
//
//
//template<typename T>
//void Encode(const std::string& input_path, const std::string& output_path)
//{
//	std::string input;
//	ReadFile(input, input_path);
//
//	BitStream OutputBitStream;
//						// 99 printable characters =>
//	size_t bits = 7;	// 99 = 0b1100011 => 7 bits
//	size_t code = 2;	// 0 increase code size by 1 bit
//						// 1 reset dictionary
//	size_t max_bits = sizeof(T) * 8;
//	
//	auto dictionary_ptr = CreateDictionary<T>(code);
//	auto& dictionary = *dictionary_ptr;
//
//	size_t code_max_size = pow(2, bits);
//
//	auto current = dictionary[input[0]];
//	for (size_t i = 1; i < input.size(); i++) {
//		if (code > code_max_size) {
//			if (bits + 1 <= max_bits) {
//				OutputBitStream.EMIT(0, bits);
//				bits++;
//				code_max_size = pow(2, bits);
//			}
//			else {
//				OutputBitStream.EMIT(1, bits);
//				bits = 7;
//				code_max_size = pow(2, bits);
//				delete dictionary_ptr;
//				code = 2;
//				dictionary_ptr = CreateDictionary<T>(code);
//				dictionary = *dictionary_ptr;
//				current = dictionary[input[i - 1]];
//			}
//		}
//		char c = input[i];
//		if (!current->m_Next[c]) {
//			current->m_Next[c] = new LetterEntry<T>(code++);
//			OutputBitStream.EMIT(current->m_Code, bits);
//			current = dictionary[c];
//			continue;
//		}
//		current = current->m_Next[c];
//	}
//	OutputBitStream.EMIT(current->m_Code, bits);
//
//	_sleep(3000);
//
//	std::ofstream fout;
//	fout.open(output_path, std::ios::binary);
//	fout << OutputBitStream.CREATE_STRING();
//	fout.close();
//	delete dictionary_ptr;
//}

template<typename T>
void CreateBaseDictionary(std::unordered_map<std::string, T>& dict, size_t& code)
{
	dict.reserve(Ascii.size());
	for (size_t i = 0; i < Ascii.size(); i++)
		dict[std::string("") + Ascii[i]] = code++;
}

template<typename T>
void Encode(const std::string& input_path, const std::string& output_path)
{
	BitStream OutputBitStream;

	std::string input;
	ReadFile(input, input_path);

	// 99 printable characters =>
	size_t bits = 7;	// 99 = 0b1100011 => 7 bits
	size_t code = 2;	// 0 increase code size by 1 bit
						// 1 reset dictionary
	size_t max_bits = sizeof(T) * 8;
	size_t code_max_size = pow(2, bits);

	std::unordered_map<std::string, T> Dictionary;
	CreateBaseDictionary(Dictionary, code);

	std::string prev = "";

	prev += input[0];

	for (size_t i = 1; i < input.size(); i++) {
		if (code > code_max_size) {
			if (bits + 1 <= max_bits) {
				OutputBitStream.EMIT(0, bits);
				bits++;
				code_max_size = pow(2, bits);
			}
			else {
				if (prev.size() > 1) {
					OutputBitStream.EMIT(Dictionary[prev], bits);
					prev = input[i - 1];
				}
				else
					prev = input[i++];
				OutputBitStream.EMIT(1, bits);
				bits = 7;
				code_max_size = pow(2, bits);
				code = 2;
				Dictionary.clear();
				CreateBaseDictionary(Dictionary, code);
			}
		}
		char current = input[i];
		if (Dictionary.find(prev + current) == Dictionary.end()) {
			OutputBitStream.EMIT(Dictionary[prev], bits);
			Dictionary[prev + current] = code++;
			prev = current;
		}
		else
			prev += current;
	}
	OutputBitStream.EMIT(Dictionary[prev], bits);

	std::ofstream fout;
	fout.open(output_path, std::ios::binary);
	fout << OutputBitStream.CREATE_STRING();
	fout.close();
}

template<typename T>
void CreateBaseMap(std::unordered_map<T, std::string>& map, size_t& code)
{
	map.reserve(Ascii.size());
	for (size_t i = 0; i < Ascii.size(); i++)
		map[code++] = Ascii[i];
}

template<typename T>
void InterpretBinary(const std::string& str, std::vector<T>& output)
{
	size_t bits = 8;

	std::vector<bool> binaryData;
	binaryData.reserve(str.size() * 8);

	for (size_t i = 0; i < str.size() - 1; i++)
		for (char j = 0; j < 8; j++)
			binaryData.emplace_back(str[i] & (0b10000000 >> j));

	char padding = str[str.size() - 1];
	binaryData.resize(binaryData.size() - padding);

	T val = 0;
	for (size_t i = 0; i < binaryData.size();) {
		for (size_t j = 0; j < bits; j++, i++) {
			val <<= 1;
			val |= binaryData[i];
		}
		if (val == 0) {
			bits++;
			continue;
		}
		if (val == 1)
			bits = 7;
		output.push_back(val);
		val = 0;
	}
}

template<typename T>
void Decode(const std::string& input_path, const std::string& output_path)
{
	size_t code = 2;

	std::string output;

	std::vector<T> input;
	{
		std::string tmp;
		ReadFile(tmp, input_path);
		InterpretBinary(tmp, input);
	}

	std::unordered_map<T, std::string> map;
	CreateBaseMap(map, code);

	std::string last = map[input[0]];
	output += last;
	for (size_t i = 1; i < input.size(); i++) {
		if (input[i] == 1) {
			map.clear();
			code = 2;
			CreateBaseMap(map, code);
			last = input[i - 1];
			continue;
		}
		if (map.find(input[i]) != map.end()) {
			output += map[input[i]];
			std::string entry = last + map[input[i]][0];
			last = map[input[i]];
			map[code++] = entry;
		}
		else {
			std::string entry = last + last[0];
			output += entry;
			map[code++] = entry;
			last = entry;
		}
	}

	std::ofstream fout;
	fout.open(output_path, std::ios::binary);
	fout << output;
	fout.close();
}

int main()
{
	Encode<uint8_t>("INPUT.txt", "OUT.txt");
	Decode<uint64_t>("OUT.txt", "OUTPUT.txt");
}


//void CreateBlock(size_t& i, const std::string& input, std::string& output)
//{
//	std::unordered_map<std::string, uint16_t> dictionary;
//	const uint32_t lvl1 = pow(2, 8 * 1);
//	const uint32_t lvl2 = pow(2, 8 * 2);
//	std::string entry = "";
//	uint16_t currentLVL = 1;
//	size_t index = 2;
//	CreateBaseDictionary(index, dictionary);
//
//	for (; i < input.size(); i++) {
//		entry += input[i];
//		while (dictionary.find(entry) != dictionary.end() && i < input.size())
//			entry += input[++i];
//		std::string tmp = entry;
//		tmp.pop_back();
//		if (currentLVL == 1)
//			output += (uint8_t)dictionary[tmp];
//		else {
//			uint8_t msb = dictionary[tmp] >> 8;
//			uint8_t lsb = (dictionary[tmp] << 8) >> 8;
//			output += msb;
//			output += lsb;
//		}
//		dictionary[entry] = ++index;
//		if (dictionary.size() + 2 == lvl1) {
//			currentLVL = 2;
//			output += '\0';
//		}
//		else
//			if (dictionary.size() + 2 == lvl2) {
//				output += '\0';
//				output += '\1';
//				return;
//			}
//	}
//}
// 
//int main()
//{
//	std::string input;
//	ReadFile(input, "INPUT.txt");
//
//	
//	std::string output = "";
//	size_t i = 0;
//
//
//
//	std::cout << ">NEEDED PROGRESS: " << input.size() << '\n';
//
//	while (i < input.size()) {
//
//		CreateBlock(i, input, output);
//		std::cout << "Current Progress: " << i << '\n';
//		std::ofstream fout;
//		fout.open("OUT.txt", std::ios::binary | std::ios::app);
//		fout << output;
//		fout.close();
//		output.clear();
//	}
//}