#pragma once
#include "BasicFormula.h"

struct ComplexFormula
{
	ComplexFormula(const std::string& input) {

	}

	std::string FormulaString;
	std::vector<BasicFormula> FormulaComponents;
};