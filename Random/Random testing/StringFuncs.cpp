#define _CRT_SECURE_NO_WARNINGS
// functions strcpy and strcat are unsafe as they can cause buffer overrun
#include <iostream>
#include <string>

const std::string Lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum tellus ex, rutrum at eros quis, bibendum lacinia turpis. Sed at placerat est. Morbi ullamcorper tortor vel mattis dignissim. Etiam sit amet euismod orci. Interdum et malesuada fames ac ante ipsum primis in faucibus. Donec eu eros sit amet felis varius consectetur. Morbi ut gravida tellus. Fusce ut elit purus. Quisque iaculis risus eget urna tincidunt, eu sagittis quam pellentesque.";
const std::string LoremP2 = "Nulla interdum quam nec tincidunt pellentesque. Pellentesque eget velit aliquet, mattis est id, eleifend eros. Praesent faucibus lorem erat, ut pulvinar ex semper imperdiet. Sed ac gravida sapien. Fusce elementum, dui quis sollicitudin tincidunt, urna ex euismod odio, a iaculis mi ex id justo. Sed tempus magna nec tempor eleifend. Mauris aliquet odio ac dui fermentum tincidunt. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum ut placerat tortor. Mauris in tortor sit amet tortor accumsan rhoncus. Nam iaculis et leo vel placerat. Donec id mollis nisl. Sed consectetur tempus orci vel tempor. Donec accumsan magna vitae erat semper, nec pellentesque erat suscipit. Praesent feugiat est vitae vehicula sodales. Vestibulum consequat urna tempor ante lacinia bibendum.";

int main()
{
	{
		char* copy = new char[Lorem.size() + 1]; // +1 for \0
		strcpy(copy, Lorem.c_str());

		std::string copy2 = Lorem;

		printf("Base String:\n%s\n\n", Lorem.c_str());
		printf("strcpy:\n%s\n\nstring copy constructor:\n%s\n",  copy, copy2.c_str());
		puts("\n\n");
	}
	{
		std::string copy = Lorem;
		char* concatenated = new char[Lorem.size() + LoremP2.size() + 2]; // +2 for \n, \0
		strcpy(concatenated, Lorem.c_str());
		strcat(concatenated, "\n");
		strcat(concatenated, LoremP2.c_str());

		std::string concatenated2 = Lorem + '\n' + LoremP2;

		printf("Base Strings:\n%s\n\n%s\n\n", Lorem.c_str(), LoremP2.c_str());
		printf("strcat:\n%s\n\n.operator+():\n%s\n", concatenated, concatenated2.c_str());
		puts("\n\n");
	}
	{
		size_t size = strlen(Lorem.c_str());
		size_t size2 = Lorem.size();
		size_t size3 = Lorem.length();

		printf("Base String:\n%s\n\n", Lorem.c_str());
		printf("strlen: %u\n.size(): %u\n.length(): %u\n", size, size2, size3);
		puts("\n\n");
	}
	{
		std::string copy = Lorem;
		printf("S1:\n%s\n\nS2:\n%s\n\nS3:\n%s\n\n", Lorem.c_str(), LoremP2.c_str(), copy.c_str());
		printf("strmcp(S1, S3): %d\n",strcmp(Lorem.c_str(), copy.c_str()));
		printf("strmcp(S1, S2): %d\n",strcmp(Lorem.c_str(), LoremP2.c_str()));
		printf("strmcp(S2, S1): %d\n", strcmp(LoremP2.c_str(), Lorem.c_str()));
		printf(".compare() (S1, S3): %d\n", Lorem.compare(copy));
		printf(".compare() (S1, S2): %d\n", Lorem.compare(LoremP2));
		printf(".compare() (S2, S1): %d\n", LoremP2.compare(Lorem));
		printf(".operator==() (S1, S3): %d\n",(Lorem == copy));
		printf(".operator==() (S1, S2): %d\n",(Lorem == LoremP2));
		printf(".operator==() (S2, S1): %d\n", (LoremP2 == Lorem));
		puts("\n\n");
	}
	{
		const char* position_Pointer = strchr(Lorem.c_str(), 'i');
		size_t position_Pointer_index = position_Pointer - Lorem.c_str();
		size_t position_index = Lorem.find('i');

		const char* position_Pointer2 = strchr(Lorem.c_str(), 'w');
		size_t position_index2 = Lorem.find('w');

		printf("Base String:\n%s\n\n", Lorem.c_str());
		printf("strchr(Base, 'i') (base ptr - returned ptr): %d\n.find('i'): %u\n",
			position_Pointer_index, position_index);
		printf("strchr(Base, 'w') (ptr == nullptr): %d\n.find('w') (val == std::string::npos): %u\n",
			(position_Pointer2 == nullptr), (position_index2 == std::string::npos));
		puts("\n\n");
	}
	{
		const char* position_Pointer = strstr(Lorem.c_str(), "ipsum");
		size_t position_Pointer_index = position_Pointer - Lorem.c_str();
		size_t position_index = Lorem.find("ipsum");

		const char* position_Pointer2 = strstr(Lorem.c_str(), "NOOM");
		size_t position_index2 = Lorem.find("NOOM");

		printf("Base String:\n%s\n\n", Lorem.c_str());
		printf("strstr(Base, \"ipsum\") (base ptr - returned ptr): %d\n.find(\"ipsum\"): %u\n",
			position_Pointer_index, position_index);
		printf("strstr(Base, \"NOOM\") (ptr == nullptr): %d\n.find(\"NOOM\") (val == std::string::npos): %u\n",
			(position_Pointer2 == nullptr), (position_index2 == std::string::npos));
		puts("\n\n");
	}
}