#include "Commons.h"
#include "Compiler.h"

namespace Compiler {
	namespace C2 {

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

		void Other()
		{
			EmitLn(std::string("") + GetName());
		}

		std::string NewLabel()
		{
			std::string S = std::string("L") + char(LCount / 10 % 10 + '0') + char(LCount % 10 + '0');
			LCount++;
			return S;
		}
		void PostLabel(const std::string& L) { printf((L + ':').c_str()); }

		void Condition()
		{
			EmitLn("<condition>");
		}

		void DoIf(const std::string& L)
		{
			std::string L1, L2;
			Match('i');
			Condition();
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
			Condition();
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
			Condition();
			EmitLn("BEQ " + L1);
			PostLabel(L2);
		}

		void Expression()
		{
			EmitLn("<expr>");
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
			while (IsNotIn(Look, "elu")) {
				switch (Look) {
					case 'i': DoIf(L); break;
					case 'w': DoWhile(); break;
					case 'p': DoLoop(); break;
					case 'r': DoRepeat(); break;
					case 'f': DoFor(); break;
					case 'd': DoDo(); break;
					case 'b': DoBreak(L); break;
					default: Other(); break;
				}
			}
		}

		void DoProgram()
		{
			Block("");
			if (Look != 'e')
				Expected("End");
			EmitLn("END");
		}
	}
}

