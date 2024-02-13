#pragma once
#include <array>
#include "Element.h"

const static struct PeriodicTable
{
public:
	const Element& operator[](int AtomicNumber) const {
		return m_PeriodicTable[AtomicNumber - 1];//-1 to keep the right atomic number
	}
	const Element& operator[](const std::string& Notation) const {
		return m_PeriodicTable[StringToAtomicNumber.at(Notation) - 1];
	}
private:
	static const std::array<Element, 118> m_PeriodicTable;
} PeriodicTable;