#include "Commons.h"


struct BitStream {
	std::vector<bool> m_bitData;

	template<typename T>
	void EMIT(T value, size_t bitsNr) {
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
		uint8_t padding = 0;
		if (bitsWritten) {
			while (bitsWritten != 8) {
				padding++;
				bitsWritten++;
				byte <<= 1;
			}
			output += byte;
		}
		output += padding;	// add a byte to the end of output
							// to represent padding of last byte

		return output;
	}
};

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
	size_t code = 1;	// 0 increase code size by 1 bit
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
			else
				throw "NOT ENOUGH BITS TO ENCODE THIS";
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

	std::string output = OutputBitStream.CREATE_STRING();

	printf("\nCompression Ratio: %f\n", double(input.size()) / output.size());

	std::ofstream fout;
	fout.open(output_path, std::ios::binary);
	fout << output;
	fout.close();
}

int main(int argc, char* argv[])
{
	std::string inputPath, outputPath;
	CLI(argc, argv, inputPath, outputPath, "INPUT.txt", "OUT.txt");
	Encode<uint64_t>(inputPath, outputPath);
}