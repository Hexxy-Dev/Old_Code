#pragma once
#include <string>
#include "../Constants/Notations.h"

const struct Element
{
	const std::string FullName;
	const std::string Notation;
	const float AtomicMass;
	float Mass() const {
		if ((int)trunc(AtomicMass * 100) % 100 == 45)
			return trunc(AtomicMass) + 0.5f;
		return round(AtomicMass);
	}
	int AtomicNumber() const {
		return StringToAtomicNumber.at(Notation);
	}
};
