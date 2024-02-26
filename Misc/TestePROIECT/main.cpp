#include <iostream>
#include <fstream>
#include <string>

char debugLevel = 1;
void Admis(const std::string& an, const std::string& tip, const double& Scor)
{
	if (an == "2021") {
		if (tip == "iulie") {
			if (Scor >= 6.98)
				printf("BUGET");
			else
				if (Scor >= 6.83)
					printf("TAXA");
				else
					printf("RESPINS");
		}
		if (tip == "septembrie") {
			if (Scor >= 8.50)
				printf("BUGET");
			else
				if (Scor >= 8.55)
					printf("TAXA");
				else
					printf("RESPINS");
		}
	}
	if (an == "2022") {
		if (tip == "iulie" || tip == "concurs") {
			if (Scor >= 8.75)
				printf("BUGET");
			else
				if (Scor >= 8.57)
					printf("TAXA");
				else
					printf("RESPINS");
		}
		if (tip == "septembrie") {
			if (Scor >= 9.30)
				printf("TAXA");
			else
				printf("RESPINS");
		}
	}
}

short BufferGreseli[2][3][30];

void Greseala(const std::string& an, const std::string& tip, const char& nrExercitiu)
{
	if (an == "2021") {
		if (tip == "iulie")
			BufferGreseli[0][1][nrExercitiu]++;
		if (tip == "septembrie")
			BufferGreseli[0][2][nrExercitiu]++;
	}
	if (an == "2022") {
		if (tip == "concurs")
			BufferGreseli[1][0][nrExercitiu]++;
		if (tip == "iulie")
			BufferGreseli[1][1][nrExercitiu]++;
		if (tip == "septembrie")
			BufferGreseli[1][2][nrExercitiu]++;
	}
}

void ArataGreseli()
{
	printf("    E:");
	for (char i = 0; i < 30; i++)
		printf("%d%s", i + 1, (i + 1 > 9 ? " " : "  "));

	printf("\n2021I:");
	for (char i = 0; i < 30; i++)
		printf("%d%s", BufferGreseli[0][1][i], (BufferGreseli[0][1][i] > 9 ? " " : "  "));
	printf("\n2021S:");
	for (char i = 0; i < 30; i++)
		printf("%d%s", BufferGreseli[0][2][i], (BufferGreseli[0][2][i] > 9 ? " " : "  "));

	printf("\n2022C:");
	for (char i = 0; i < 30; i++)
		printf("%d%s", BufferGreseli[1][0][i], (BufferGreseli[1][0][i] > 9 ? " " : "  "));
	printf("\n2022I:");
	for (char i = 0; i < 30; i++)
		printf("%d%s", BufferGreseli[1][1][i], (BufferGreseli[1][1][i] > 9 ? " " : "  "));
	printf("\n2022S:");
	for (char i = 0; i < 30; i++)
		printf("%d%s", BufferGreseli[1][2][i], (BufferGreseli[1][2][i] > 9 ? " " : "  "));
}

bool BufferGreseliUltimulTest[30];

void Verifica(const std::string& an, const std::string& tip, const std::string& nume)
{
	printf("%s %s %s:\n",an.c_str(),tip.c_str(),nume.c_str());

	std::string r, r2;
	char posibile[] = "ABCD";
	double Scor = 10.0;
	char Greseli = 0;
	char Lipsa = 0;

	std::ifstream fin(std::string("./") + an + '/' + tip + '/' + "r.txt");
	std::ifstream fin2(std::string("./") + an + '/' + tip + '/' + nume + ".txt");

	for (char nrExercitiu = 0; nrExercitiu < 30; nrExercitiu++) {
		char corecte = 0, gresite = 0, lipsa = 0, raspunsuri = 0;

		std::getline(fin, r);
		std::getline(fin2, r2);
		
		for (int i = 0; i < 4; i++)
			if (r.find(posibile[i]) != std::string::npos) {
				raspunsuri++;
				if (r2.find(posibile[i]) != std::string::npos)
					corecte++;
				else
					lipsa++;
			}
			else
				if (r2.find(posibile[i]) != std::string::npos)
					gresite++;

		double raspuns = 3 / (double)raspunsuri;
		double scor = raspuns * corecte - 0.66 * raspuns * gresite;
		if (scor < 0)
			scor = 0;

		Scor += scor;
		Greseli += gresite;
		Lipsa += lipsa;

		if(gresite || lipsa) {
			BufferGreseliUltimulTest[nrExercitiu] = true;
			if(debugLevel)
				Greseala(an, tip, nrExercitiu);
		}

		if (debugLevel == 3)
			printf("%d:%s%.2f\n", nrExercitiu + 1, (nrExercitiu + 1 > 9 ? " " : "  "), scor);

		if (debugLevel == 2 && scor != 3)
			printf("%d.\n%s\n%s\n%d|%.2f\n%d|%d|%d\n\n",
				nrExercitiu + 1, r.c_str(), r2.c_str(), raspunsuri, scor, corecte, lipsa, gresite);

		if (fin2.eof()) break;
	}
	fin.close();
	fin2.close();

	Scor /= 10;

	printf("%.2f\n", Scor);
	Admis(an, tip, Scor);

	if(debugLevel >= 2)
		printf("\n%d|%d", Greseli, Lipsa);
	puts("\n");
}

int main(int argc, char **argv)
{
	std::ifstream fin("./ListaTeste.txt");
	std::string an, tip, nume;
	if(argc == 2)
		debugLevel = argv[1][0] - '0';
	while (!fin.eof()) {
		for(char i = 0; i < 30; i++)
			BufferGreseliUltimulTest[i] = false;
		fin >> an >> tip >> nume;
		Verifica(an, tip, nume);
	}
	fin.close();

	if (debugLevel)
		ArataGreseli();
	putchar('\n');

	for(char i = 0; i < 30; i++)
		if(BufferGreseliUltimulTest[i])
			printf("%d,",i+1);
}
