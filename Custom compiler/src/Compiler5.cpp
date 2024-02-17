#include "Commons.h"
#include "Compiler.h"

namespace Compiler {
	namespace C5 {

		std::string GetName()
		{
			std::string x = "";
			if (!IsAlpha(Look))
				Expected("Name");
			while (IsAlNum(Look)) {
				x += UpCase(Look);
				GetChar();
			}
			return x;
		}



	}
}