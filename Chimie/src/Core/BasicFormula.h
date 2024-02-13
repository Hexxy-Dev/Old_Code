#pragma once
#include <string>
#include <vector>
#include "Element.h"

struct FormulaElement
{
	const Element& PeriodicElement;
	char NumberOfAtoms;
};

class BasicFormula
{
public:
	BasicFormula(const std::string& input) {
		std::string elem;
		char atoms;

		FormulaString = input;
		for (size_t i = 0; i < input.length(); i++) {
			if (isalpha(input[i]) && isupper(input[i])) {
				atoms = 1;
				elem = input[i];

				if (isalpha(input[i + 1]) && islower(input[i + 1])) {
					i++;
					elem += input[i];
				}
				if (isdigit(input[i + 1])) {
					i++;
					atoms = input[i] - '0';
				}
				Elements.push_back({ PeriodicTable[elem], atoms });
			}
			else
				throw "Input is not a valid formula";
		}
	}

	std::string FormulaString;
	std::vector<FormulaElement> Elements;

	float Mass() const {
		float output = 0.0f;
		for (const auto& element : Elements)
			output += element.PeriodicElement.Mass() * element.NumberOfAtoms;
		return output;
	}
};