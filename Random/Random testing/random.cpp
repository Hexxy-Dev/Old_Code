#include <iostream>

using namespace std;

void PrintingData(const int s, const int w, const int outer, const int inner, string& output)
{
	for (int k = 0; k < outer; k++)
		output += ' ';
	for (char k = 0; k < w; k++)
		output += '#';
	for (int k = 0; k < inner; k++)
		output += ' ';
	for (char k = 0; k < w + (inner < 0) * inner; k++)
		output += '#';
	for (int k = 0; k < outer; k++)
		output += ' ';
	output += '\n';
}

int main()
{
	int s = 30, w = 3;
	int outer = 0, inner;
	inner = s - w * 2;
	string output = "";
	for (; outer * 2 + w + abs(w + (inner < 0) * inner) <= s; outer++, inner -= 2)
		PrintingData(s, w, outer, inner, output);
	outer -= 1 + 1 * (w > 1);
	inner += 2 + 2 * (w > 1);
	for (; outer >= 0; outer--, inner += 2)
		PrintingData(s, w, outer, inner, output);
	puts(output.c_str());
}