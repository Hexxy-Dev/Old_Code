#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>


const uint8_t END_PADDING = 2;

void CLI(int argc, char* argv[], std::string& inputPath, std::string& outputPath,
	const std::string& defaultInputPath, const std::string& defaultOutputPath)
{
	inputPath = defaultInputPath;
	outputPath = defaultOutputPath;
	if (argc < 2)
		printf("USAGE:"
			"\n\tREQ: Input file path       (def = \"%s\")"
			"\n\tREQ: Output file path      (def = \"%s\")"
			"\n", defaultInputPath.c_str(), defaultOutputPath.c_str());
	if (argc == 3) {
		inputPath = argv[1];
		outputPath = argv[2];
	}
}

void ReadFile(std::string& input, const std::string& path)
{
	std::ifstream fin;
	fin.open(path, std::ios::binary);

	if (fin.fail())
		throw "Cannot open file";

	input.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
	fin.close();
}