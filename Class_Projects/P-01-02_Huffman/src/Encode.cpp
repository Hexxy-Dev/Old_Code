#include "Commons.h"

struct Node {
	Node(size_t weight, Node* left, Node* right)
		: c('\0'), weight(weight), left(left), right(right)
	{
		references.push_back(this);
	}
	Node(std::pair<char, size_t> pair)
		: c(pair.first), weight(pair.second), left(nullptr), right(nullptr)
	{
		references.push_back(this);
	}
	char c;
	size_t weight;

	Node* left;
	Node* right;

	static std::vector<Node*> references;

	bool operator>(const Node& other) const { return (weight > other.weight); }
	bool operator<(const Node& other) const { return (weight < other.weight); }
};
std::vector<Node*> Node::references;


class PointerCompare {
public:
	template<typename T>
	bool operator()(T a, T b) { return (*a) > (*b); }
};

Node* GetMaxPriority(std::priority_queue<Node*, std::vector<Node*>, PointerCompare>& primaryQueue,
	std::priority_queue<Node*, std::vector<Node*>, PointerCompare>& secondaryQueue)
{
	Node* ptr;
	if (primaryQueue.size()) {
		if (secondaryQueue.size()) {
			if (*primaryQueue.top() < *secondaryQueue.top()) {
				ptr = primaryQueue.top();
				primaryQueue.pop();
			}
			else {
				ptr = secondaryQueue.top();
				secondaryQueue.pop();
			}
		}
		else {
			ptr = primaryQueue.top();
			primaryQueue.pop();
		}
	}
	else {
		ptr = secondaryQueue.top();
		secondaryQueue.pop();
	}

	return ptr;
}

Node* GenerateTree(std::unordered_map<char, size_t>& frequencyMap)
{
	std::priority_queue <Node*, std::vector<Node*>, PointerCompare> primaryQueue;
	for (const auto& pair : frequencyMap)
		primaryQueue.push(new Node(pair));

	std::priority_queue<Node*, std::vector<Node*>, PointerCompare> secondaryQueue;

	Node* left;
	Node* right;

	while (primaryQueue.size() || secondaryQueue.size() > 1) {

		left = GetMaxPriority(primaryQueue, secondaryQueue);
		right = GetMaxPriority(primaryQueue, secondaryQueue);

		secondaryQueue.push(new Node(left->weight + right->weight, left, right));
	}

	return secondaryQueue.top();
}

void CreateLetterMaps(std::unordered_map<char, std::string>& letterMap, Node* root, std::string code = "")
{
	if (!root)
		return;
	if (root->left == nullptr && root->right == nullptr)
		letterMap[root->c] = code;

	CreateLetterMaps(letterMap, root->left, code + '\0');
	CreateLetterMaps(letterMap, root->right, code + '\1');
}

void CreateDictionary(std::vector<bool>& dictionary, std::unordered_map<char, std::string>& letterMap, uint8_t PADDING)
{
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

		dictionary.push_back(0);
		for (size_t i = 0; i < PADDING - 1; i++)
			dictionary.push_back(1);
	}
	for (size_t k = 0; k < END_PADDING; k++) {
		dictionary.push_back(0);
		for (size_t i = 0; i < PADDING - 1; i++)
			dictionary.push_back(1);
	}
}

void CreateBinaryData(std::vector<bool>& binaryData, std::unordered_map<char, std::string>& letterMap,
	uint8_t PADDING, size_t total, const std::string& input)
{
	binaryData.reserve(total);
	for (char c : input)
		for (char c2 : letterMap[c])
			binaryData.emplace_back(c2);

	binaryData.push_back(0);
	for (size_t i = 0; i < PADDING - 1; i++)
		binaryData.push_back(1);
}

inline void AddBit(std::string& stringOutput, char& o, char& bits, char val)
{
	o <<= 1;
	o |= val;
	bits++;
	if (bits == 8) {
		bits = 0;
		stringOutput += o;
	}
}

double WRITE_DATA_TO_FILE(std::vector<bool>& dictionary, std::vector<bool>& binaryData, const std::string& path)
{
	std::string stringOutput;
	char o = 0;
	char bits = 0;

	for (size_t i = 1; i <= dictionary.size(); i++)
		AddBit(stringOutput, o, bits, dictionary[i - 1]);

	for (size_t i = 1; i <= binaryData.size(); i++)
		AddBit(stringOutput, o, bits, binaryData[i - 1]);

	while (bits != 0)
		AddBit(stringOutput, o, bits, 0);

	std::ofstream fout(path, std::ios::binary);
	fout << stringOutput;
	fout.close();

	return stringOutput.size();
}

void Encode(const std::string& inputPath, const std::string& outputPath)
{
	std::string input;
	ReadFile(input, inputPath);

	std::unordered_map<char, size_t> frequencyMap;
	for (char c : input)
		frequencyMap[c]++;


	Node* root = GenerateTree(frequencyMap);


	std::unordered_map<char, std::string> letterMap;
	CreateLetterMaps(letterMap, root);


	uint8_t PADDING = 0;
	size_t total = 0;
	for (const auto& pair : letterMap) {
		total += pair.second.size() * frequencyMap[pair.first];
		PADDING = PADDING < pair.second.size() ? pair.second.size() : PADDING;
	}


	std::vector<bool> dictionary;
	CreateDictionary(dictionary, letterMap, PADDING);


	std::vector<bool> binaryData;
	CreateBinaryData(binaryData, letterMap, PADDING, total, input);


	double output_size = WRITE_DATA_TO_FILE(dictionary, binaryData, outputPath);

	printf("\nCompression Ratio: %f\n", double(input.size()) / output_size);

	for (size_t i = 0; i < Node::references.size(); i++)
		delete Node::references[i];
}

int main(int argc, char* argv[])
{
	std::string inputPath, outputPath;
	CLI(argc, argv, inputPath, outputPath, "INPUT.txt", "OUT.txt");
	Encode(inputPath, outputPath);
}