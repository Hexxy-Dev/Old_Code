#include <fstream>


int main(int argc, char *argv[])
{
	std::ofstream fout("Path.txt");
	fout << argv[1];
	fout.close();
}
