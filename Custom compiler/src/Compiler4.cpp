#include "Commons.h"
#include "Compiler.h"

namespace Compiler {
	namespace C4 {


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


		void Assignment()
		{
			char Name = GetName();
			Match('=');
			BoolExpression();
			EmitLn(std::string("LEA ") + Name + "(PC),A0");
			EmitLn("MOVE D0,(A0)");
		}

		///////////////

		std::string NewLabel()
		{
			std::string S = std::string("L") + char(LCount / 10 % 10 + '0') + char(LCount % 10 + '0');
			LCount++;
			return S;
		}
		void PostLabel(const std::string& L) { printf((L + ':').c_str()); }

		void DoIf(const std::string& L)
		{
			std::string L1, L2;
			Match('i');
			BoolExpression();
			L1 = NewLabel();
			L2 = L1;
			EmitLn("BEQ " + L1);
			Block(L);
			if (Look == 'l') {
				Match('l');
				L2 = NewLabel();
				EmitLn("BRA " + L2);
				PostLabel(L1);
				Block(L);
			}
			Match('e');
			PostLabel(L2);
		}

		void DoWhile()
		{
			std::string L1, L2;
			Match('w');
			L1 = NewLabel();
			L2 = NewLabel();
			PostLabel(L1);
			BoolExpression();
			EmitLn("BEQ " + L2);
			Block(L2);
			Match('e');
			EmitLn("BRA " + L1);
			PostLabel(L2);
		}

		void DoLoop()
		{
			std::string L1, L2;
			Match('p');
			L1 = NewLabel();
			L2 = NewLabel();
			Block(L2);
			Match('e');
			EmitLn("BRA " + L1);
			PostLabel(L2);
		}

		void DoRepeat()
		{
			std::string L1, L2;
			Match('r');
			L1 = NewLabel();
			L2 = NewLabel();
			PostLabel(L1);
			Block(L2);
			Match('u');
			BoolExpression();
			EmitLn("BEQ " + L1);
			PostLabel(L2);
		}

		void DoFor()
		{
			std::string L1, L2;
			char Name;
			Match('f');
			L1 = NewLabel();
			L2 = NewLabel();
			Name = GetName();
			Match('=');
			Expression();
			EmitLn("SUBQ #1,D0");
			EmitLn(std::string("LEA ") + Name + "(PC),A0");
			EmitLn("MOVE D0,(A0)");
			Expression();
			EmitLn("MOVE D0,-(SP)");
			PostLabel(L1);
			EmitLn(std::string("LEA ") + Name + "(PC),A0");
			EmitLn("MOVE (A0),D0");
			EmitLn("ADDQ #1,D0");
			EmitLn("MOVE D0,(A0)");
			EmitLn("CMP (SP),D0");
			EmitLn("BGT " + L2);
			Block(L2);
			Match('e');
			EmitLn("BRA " + L1);
			PostLabel(L2);
			EmitLn("ADDQ #2,SP");
		}

		void DoDo()
		{
			std::string L1, L2;
			Match('d');
			L1 = NewLabel();
			L2 = NewLabel();
			Expression();
			EmitLn("SUBQ #1,D0");
			PostLabel(L1);
			EmitLn("MOVE D0,-(SP)");
			Block(L2);
			EmitLn("MOVE (SP)+,D0");
			EmitLn("DBRA D0," + L1);
			EmitLn("SUBQ #2,SP");
			PostLabel(L2);
			EmitLn("ADDQ #2,SP");
		}

		void DoBreak(const std::string& L)
		{
			Match('b');
			if (L != "")
				EmitLn("BRA " + L);
			else
				Abort("No loop to break from");
		}

		void Block(const std::string& L)
		{
			while (IsNotIn(Look, "elu") && Look != '\0') {
				Fin();
				switch (Look) {
					case 'i': DoIf(L); break;
					case 'w': DoWhile(); break;
					case 'p': DoLoop(); break;
					case 'r': DoRepeat(); break;
					case 'f': DoFor(); break;
					case 'd': DoDo(); break;
					case 'b': DoBreak(L); break;
					default: Assignment(); break;
				}
				Fin();
			}
		}

		void DoProgram()
		{
			Block("");
			EmitLn("END");
		}
	}
}