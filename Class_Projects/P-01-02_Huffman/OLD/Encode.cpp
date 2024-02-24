#include "Huffman.h"
#include "Utility.h"

void Encrypt()
{
	std::string input;
	std::ifstream fin;
	fin.open("INPUT VERY LONG.txt", std::ios::binary);
	if (fin.fail()) {
		puts("Cannot open file");
		return;
	}
	input.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
	fin.close();

	//puts(input.c_str());

	//input = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890!@#$%^&*()-_=+`~,./<>?;'\\:\"|[]{} \n";

	std::unordered_map<char, size_t> frequencyMap;
	for (char c : input)
		frequencyMap[c]++;

	std::priority_queue <Node*, std::vector<Node*>, PointerCompare> primaryQueue;
	for (const auto& pair : frequencyMap)
		primaryQueue.push(new Node(pair));


	//PrintQueue(primaryQueue);

	Node* root = GenerateTree(primaryQueue);

	//Traverse(root);
	//print(root);


	std::unordered_map<char, std::string> letterMap;
	CreateLetterMaps(letterMap, root);

	size_t total = 0;
	for (const auto& pair : letterMap)
		total += pair.second.size() * frequencyMap[pair.first];



	//{
	//	std::string stringOutput;
	//	stringOutput.reserve(total);
	//	for (char c : input)
	//		for (char c2 : letterMap[c]) {
	//			stringOutput.push_back(c2 + '0');
	//		}
	//	std::cout << total;
	//	puts("\n");
	//	puts(stringOutput.c_str());
	//}


	uint8_t max = 0;

	for (auto pair : letterMap)
		max = max < pair.second.size() ? pair.second.size() : max;

	uint8_t PADDING = max;

	std::vector<bool> dictionary;

	for (size_t i = 0; i < 8; i++)
		dictionary.push_back(PADDING & (0b10000000 >> i));

	for (auto pair : letterMap) {
		for (char c : pair.second)
			dictionary.push_back(c);

		char c = pair.first;
		for (size_t i = 0; i < 8; i++) {
			dictionary.push_back(c & 0b10000000);
			c <<= 1;
		}
		for (size_t k = 0; k < 1; k++) {
			dictionary.push_back(0);
			for (size_t i = 0; i < PADDING - 1; i++)
				dictionary.push_back(1);
		}
	}
	for (size_t k = 0; k < END_PADDING; k++) {
		dictionary.push_back(0);
		for (size_t i = 0; i < PADDING - 1; i++)
			dictionary.push_back(1);
	}



	std::vector<bool> binaryData;

	binaryData.reserve(total);
	for (char c : input)
		for (char c2 : letterMap[c])
			binaryData.emplace_back(c2);

	binaryData.push_back(0);
	for (size_t i = 0; i < PADDING - 1; i++)
		binaryData.push_back(1);


	WRITE_DATA_TO_FILE(dictionary, binaryData);


	//{
	//	std::cout << '\n';
	//	std::string s;
	//	for (auto b : dictionary)
	//		s += b + '0';
	//	puts(s.c_str());
	//}
}

int main()
{
	Encrypt();
}