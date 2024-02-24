#include <iostream>
#include <functional>
#include <conio.h>
#include <vector>


class Questionnaire {
public:
	bool showExplanations = false;
	std::vector<std::function<void(void)>> questions;

	template<typename T>
	void Question(const std::string& text, T a, T b, T c, T correct, size_t points,
		std::string explanation = "")
	{
		currentIndex++;
		maxPoints += points;
		std::cout << points << " p - " << currentIndex << '\n';
		puts(text.c_str());
		std::cout << "\ta) " << a << "\n\tb) " << b << "\n\tc) " << c << '\n';
		char answer;
		while (true) {
			answer = getch();
			if (answer >= 'a' && answer <= 'c')
				break;
		}
		std::cout << "\nChosen answer: " << answer << "\n\n\n";
		switch (answer) {
		case 'a': if (a == correct) totalPoints += points; else failed.push_back(currentIndex); break;
		case 'b': if (b == correct) totalPoints += points; else failed.push_back(currentIndex); break;
		case 'c': if (c == correct) totalPoints += points; else failed.push_back(currentIndex); break;
		}
		if (explanation != "" && showExplanations) {
			puts("");
			puts(explanation.c_str());
			puts("\n\n");
		}
	}

	template<typename T>
	void Question(const std::string& text, T correct, size_t points,
		std::string explanation = "")
	{
		currentIndex++;
		maxPoints += points;
		std::cout << points << " p - " << currentIndex << '\n';
		puts(text.c_str());
		puts("Answer:");
		std::string answer;
		std::cin >> answer;
		puts("\n\n");
		if (answer == correct) totalPoints += points; else failed.push_back(currentIndex);
		if (explanation != "" && showExplanations) {
			puts("");
			puts(explanation.c_str());
			puts("\n\n");
		}
	}

	void Start()
	{
		for (auto func : questions)
			func();

		printf("Total socre: %u / %u\n", totalPoints, maxPoints);

		puts("Failed questions:");
		for (auto i : failed)
			printf("%u ", i);
		puts("\n");
	}

private:
	size_t totalPoints = 0;
	size_t maxPoints = 0;
	std::vector<uint16_t> failed;
	uint16_t currentIndex = 0;
};

#define AddQuestion(X, Y) X.questions.push_back([&](){X.Question Y;})

int main()
{
	Questionnaire questionnaire;
	questionnaire.showExplanations = true;
	AddQuestion(questionnaire,
		("According to the C++17 standard, what is the output of this program:\n"
		"\n??=include <iostream>"
		"\n%:define hmm in %:%: t"
		"\nhmm main() <%"
		"\n  hmm x = 016;"
		"\n  hmm y = compl x;"
		"\n  y = ??-y;//??/"
		"\n  ??< y = 3 ??=NOOM ??>"
		"\n  y ??'= 0xf;"
		"\n  const char* s = \"NOOM\";"
		"\n  if(x ??!??! y)"
		"\n    std::cout << y??(s??) << s<:0b0:>;"
		"\n%>\n", "ON", 100,
		"Explanation:\n"
		"trigraphs have existed all the way up to C++17\n"
		"digraphs have existed since C99 and to this day on many compilers like "
		"GCC or CLANG with the exception of MSVC which doesn't support them\n"
		"??=\t#\n??/\t\\\n??'\t^\n??(\t[\n??)\t]\n??!\t|\n??<\t{\n??>\t}\n??-\t~\n"
		"<:\t[\n:>\t]\n<%\t{\n%>\t}\n%:\t#\n"
		"compl\t~"));
	AddQuestion(questionnaire,
		("How many one-sided tetrominoes exist?", 5, 7, 19, 7, 30,
		"####   ##   ###    #   #     ##   ##\n"
		"       ##    #     #   #    ##     ##\n"
		"                  ##   ##"));
	AddQuestion(questionnaire,
		("How many ghosts are there in Pac-Man?", 2, 3, 4, 4, 30,
		"There are 4 ghosts and their names are: Inky, Blinky, Pinky and Clyde"));
	AddQuestion(questionnaire,
		("Question text", "answer 1", "answer 2", "answer 3", "answer 3", 30));
	AddQuestion(questionnaire,
		("Question text", "answer 1", "answer 2", "answer 3", "answer 3", 30));
	AddQuestion(questionnaire,
		("Question text", "answer 1", "answer 2", "answer 3", "answer 3", 30));

	questionnaire.Start();
}