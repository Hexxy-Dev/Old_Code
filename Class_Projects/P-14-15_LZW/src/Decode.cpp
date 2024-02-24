#include "Commons.h"


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
	size_t bits = 7;

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
		output.push_back(val);
		val = 0;
	}
}

template<typename T>
void Decode(const std::string& input_path, const std::string& output_path)
{
	size_t code = 1;

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

int main(int argc, char* argv[])
{
	std::string inputPath, outputPath;
	CLI(argc, argv, inputPath, outputPath, "OUT.txt", "OUTPUT.txt");
	Decode<uint64_t>(inputPath, outputPath);
}