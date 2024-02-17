#include "Commons.h"
#include "Compiler.h"

namespace Compiler {
	namespace C3 {

		char GetNum()
		{
			if (!IsDigit(Look))
				Expected("Integer");
			char output = Look;
			GetChar();
			SkipWhite();
			return output;
		}

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

		void SignedFactor()
		{
			if (Look == '+')
				GetChar();
			if (Look == '-') {
				GetChar();
				if (IsDigit(Look))
					EmitLn(std::string("MOVE #-") + GetNum() + ", D0");
				else {
					Factor();
					EmitLn("NEG D0");
				}
			}
			else
				Factor();
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
			EmitLn("EXS.L D0");
			EmitLn("DIVS D1,D0");
		}

		void Term() {
			SignedFactor();
			while (IsMulop(Look)) {
				EmitLn("MOVE D0,-(SP)");
				switch (Look) {
					case '*': Multiply(); break;
					case '/': Divide(); break;
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
			Term();
			while (IsAddop(Look)) {
				EmitLn("MOVE D0,-(SP)");
				switch (Look) {
					case '+': Add(); break;
					case '-': Subtract(); break;
				}
			}
		}

		void Equals()
		{
			Match('=');
			Expression();
			EmitLn("CMP (SP)+,D0");
			EmitLn("SEQ D0");
		}

		void NotEquals()
		{
			Match('#');
			Expression();
			EmitLn("CMP (SP)+,D0");
			EmitLn("SNE D0");
		}

		void Less()
		{
			Match('<');
			Expression();
			EmitLn("CMP (SP)+,D0");
			EmitLn("SGE D0");
		}

		void Greater()
		{
			Match('>');
			Expression();
			EmitLn("CMP (SP)+,D0");
			EmitLn("SLE D0");
		}

		void Relation()
		{
			Expression();
			if (IsRelop(Look)) {
				EmitLn("MOVE D0,-(SP)");
				switch (Look) {
					case '=': Equals(); break;
					case '#': NotEquals(); break;
					case '<': Less(); break;
					case '>': Greater(); break;
					default: break;
				}
				EmitLn("TST D0");
			}
		}

		void BoolFactor()
		{
			if (IsBoolean(Look)) {
				if (GetBoolean())
					EmitLn("MOVE #-1,D0");
				else
					EmitLn("CLR D0");
			}
			else
				Relation();
		}

		void NotFactor()
		{
			if (Look == '!') {
				Match('!');
				BoolFactor();
				EmitLn("EOR #-1,D0");
			}
			else
				BoolFactor();
		}

		void BoolTerm()
		{
			NotFactor();
			while (Look == '&') {
				EmitLn("MOVE D0,-(SP)");
				Match('&');
				NotFactor();
				EmitLn("AND (SP)+,D0");
			}
		}

		void BoolOr()
		{
			Match('|');
			BoolTerm();
			EmitLn("OR (SP)+,D0");
		}

		void BoolXor()
		{
			Match('~');
			BoolTerm();
			EmitLn("EOR (SP)+,D0");
		}

		void BoolExpression()
		{
			BoolTerm();
			while (IsOrOp(Look)) {
				EmitLn("MOVE D0,-(SP)");
				switch (Look) {
					case '|': BoolOr(); break;
					case '~': BoolXor(); break;
					default: break;
				}
			}
		}

	}
}