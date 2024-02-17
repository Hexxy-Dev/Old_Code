#include "Commons.h"
#include "Interpreter.h"

namespace Interpreter {

	int Table['Z' - 'A' + 1];

	void InitTable() {
		for (char i = 'A'; i <= 'Z'; i++)
			Table[i - 'A'] = 0;
	}

	int GetNum()
	{
		int Value = 0;
		if (!IsDigit(Look))
			Expected("Integer");
		while (IsDigit(Look)) {
			Value = Value * 10 + Look - '0';
			GetChar();
		}
		SkipWhite();
		return Value;
	}

	int Factor()
	{
		int Output;
		if (Look == '(') {
			Match('(');
			Output = Expression();
			Match(')');
		}
		else if (IsAlpha(Look))
			Output = Table[GetName()];
		else
			Output = GetNum();
		return Output;
	}

	int Term()
	{
		int Value = Factor();
		while (IsMulop(Look)) {
			switch (Look) {
				case '*':
					Match('*');
					Value *= Factor();
					break;
				case '/':
					Match('/');
					Value /= Factor();
					break;
			}
		}
		return Value;
	}

	int Expression()
	{
		int Value;
		if (IsAddop(Look))
			Value = 0;
		else
			Value = Term();
		while (IsAddop(Look)) {
			switch (Look) {
				case '+':
					Match('+');
					Value += Term();
					break;
				case '-':
					Match('-');
					Value -= Term();
					break;
				default: break;
			}
		}
		return Value;
	}

	void Assignment()
	{
		char Name = GetName();
		Match('=');
		Table[Name] = Expression();
	}

	void Input()
	{
		Match('?');
		std::cin >> Table[GetName()];
	}

	void Output()
	{
		Match('!');
		printf("%d", Table[GetName()]);
	}
}