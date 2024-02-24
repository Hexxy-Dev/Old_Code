#include <iostream>

char frames[4][3][6] = {
	{"    *",
	 "  *  ",
	 "*    " },
	{"     ",
	 "* * *",
	 "     " },
	{"*    ",
	 "  *  ",
	 "    *" },
	{"  *  ",
	 "  *  ",
	 "  *  " }
};

int main()
{
	std::string offset = "";
	for (int i = 0; i < 80; i++) {
		std::string output = ".\t\t\t\t\t\t\t\t\t\t .\n\n";
		for(int j = 0; j < 3; j++)
			output += offset + frames[i % 4][j] + '\n';
		output += ".\t\t\t\t\t\t\t\t\t\t .\n\n\n\n\n\n\n\n\n\n\n\n";
		puts(output.c_str());
		_sleep(100);
		offset += ' ';
	}
}