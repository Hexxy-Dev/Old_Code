#include "Commons.h"

void ReadBinaryData(const std::string& input, std::vector<bool>& binaryData, uint8_t& PADDING)
{
	binaryData.reserve(input.size() * 8);

	for (char c : input)
		for (char i = 0; i < 8; i++)
			binaryData.emplace_back(c & (0b10000000 >> i));

	for (int i = 0; i < 8; i++) {
		PADDING <<= 1;
		PADDING |= binaryData[i];
	}

	while (!binaryData[binaryData.size() - 1])
		binaryData.pop_back();
	binaryData.resize(binaryData.size() - PADDING);
}

void CreateDictonary(std::unordered_map<std::string, char>& dictionary, size_t& i,
	const std::vector<bool>& binaryData, uint8_t PADDING)
{
	std::vector<bool> entry;
	uint8_t paddingFound = 0;
	uint8_t terminators = 0;

	for (i = 8; i < binaryData.size(); i++) {
		if (!binaryData[i]) {
			paddingFound = 0;
		}
		paddingFound += binaryData[i];

		if (paddingFound == PADDING - 1) {
			size_t k;
			for (k = entry.size() - 1; k >= 0; k--)
				if (entry[k] == 0)
					break;
			if (k == 0) {
				terminators++;
				entry.clear();
				continue;
			}

			k--;
			char c = 0;
			for (int j = 7; j >= 0; j--) {
				c <<= 1;
				c |= entry[k - j];
			}
			k -= 7;

			std::string code;
			for (int j = 0; j < k; j++)
				code += entry[j];
			dictionary[code] = c;

			entry.clear();
			continue;
		}

		if (terminators == END_PADDING)
			break;

		entry.push_back(binaryData[i]);
	}
}

void WRITE_DATA_TO_FILE(size_t i, const std::vector<bool>& binaryData,
	std::unordered_map<std::string, char>& dictionary, const std::string& outputPath)
{
	std::string output = "";
	std::string code = "";
	for (; i < binaryData.size(); i++) {
		code += binaryData[i];

		if (dictionary.find(code) != dictionary.end()) {
			if (dictionary[code] != '\r')
				output += dictionary[code];
			code = "";
		}
	}

	std::ofstream fout;
	fout.open(outputPath);
	fout << output;
	fout.close();
}

void Decode(const std::string& inputPath, const std::string& outputPath)
{
	std::string input;
	ReadFile(input, inputPath);

	std::vector<bool> binaryData;
	uint8_t PADDING = 0;
	ReadBinaryData(input, binaryData, PADDING);


	std::unordered_map<std::string, char> dictionary;
	size_t i;
	CreateDictonary(dictionary, i, binaryData, PADDING);

	
	WRITE_DATA_TO_FILE(i, binaryData, dictionary, outputPath);
}

int main(int argc, char* argv[])
{
	std::string inputPath, outputPath;
	CLI(argc, argv, inputPath, outputPath, "OUT.txt", "OUTPUT.txt");
	Decode(inputPath, outputPath);
}