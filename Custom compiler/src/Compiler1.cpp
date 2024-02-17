#include "Commons.h"
#include "Compiler.h"

namespace Compiler {
	namespace C1 {

		char GetNum()
		{
			if (!IsDigit(Look))
				Expected("Integer");
			char output = Look;
			GetChar();
			SkipWhite();
			return output;
		}
		/*
		std::string GetNum()
		{
			std::string Token = "";
			if (!IsDigit(Look))
				Expected("Integer");
			while (IsDigit(Look)) {
				Token += Look;
				GetChar();
			}
			SkipWhite();
			return Token;
		}//*/

		void Expression();

		void Ident()
		{
			char Name = GetName();
			if (Look == '(') {
				Match('(');
				Match(')');
				EmitLn("BSR " + Name);
			}
			else
				EmitLn(std::string("MOVE ") + Name + "(PC),D0");
		}

		void Factor()
		{
			if (Look == '(') {
				Match('(');
				Expression();
				Match(')');
			}
			else if (IsAlpha(Look))
				Ident();
			else
				EmitLn(std::string("MOVE #") + GetNum() + ",D0");
		}

		void Multiply()
		{
			Match('*');
			Factor();
			EmitLn("MULS (SP)+,D0");
		}
		void Divide()
		{
			Match('/');
			Factor();
			EmitLn("MOVE (SP)+,D1");
			EmitLn("DIVS D1,D0");
		}

		void Term() {
			Factor();
			while (IsMulop(Look)) {
				EmitLn("MOVE D0,-(SP)");
				switch (Look) {
				case '*': Multiply(); break;
				case '/': Divide(); break;
				default: Expected("Mulop"); break;
				}
			}
		}

		void Add()
		{
			Match('+');
			Term();
			EmitLn("ADD (SP)+,D0");
		}
		void Subtract()
		{
			Match('-');
			Term();
			EmitLn("SUB (SP)+,D0");
			EmitLn("NEG D0");
		}

		void Expression()
		{
			if (IsAddop(Look))
				EmitLn("CLR D0");
			else
				Term();
			while (IsAddop(Look)) {
				EmitLn("MOVE D0,-(SP)");
				switch (Look) {
				case '+': Add(); break;
				case '-': Subtract(); break;
				default: Expected("Addop"); break;
				}
			}
		}

		void Assignment()
		{
			char Name = GetName();
			Match('=');
			Expression();
			EmitLn(std::string("LEA ") + Name + "(PC),A0");
			EmitLn("MOVE D0,(A0)");
		}
	}
}