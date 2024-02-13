#include <iostream>

#include "src/Chemistry.h"

int main()
{
	std::string input = "Cl";
	BasicFormula formula = BasicFormula(input);
	std::cout << formula.FormulaString << " : " << formula.Mass() << '\n';
	input = "H2O";
	formula = BasicFormula(input);
	std::cout << formula.FormulaString << " : " << formula.Mass() << '\n';
	std::cout << "Pb: " << PeriodicTable[Pb].FullName << '\n';
	std::cout << "N: " << PeriodicTable["N"].FullName << '\n';
	std::cout << "H: " << PeriodicTable[1].FullName << '\n';
}