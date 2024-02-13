#pragma once
#include "Common.h"
#include <string_view>
#include <iostream>

struct Coord
{
	explicit Coord(std::string_view move) {
		x = move[0] - 'a';
		y = '0' + BoardSizeY - move[1];
	}
	Coord(i8 x, i8 y)
		: x(x), y(y)
	{}

	i8 x;
	i8 y;

	bool IsValidPosition() {
		return ((x >= 0 && x < BoardSizeX) && (y >= 0 && y < BoardSizeY));
	}

	bool operator==(Coord other) {
		return (x == other.x && y == other.y);
	}
	bool operator!=(Coord other) {
		return !this->operator==(other);
	}
	Coord operator+(Coord other) {
		return { x + other.x, y + other.y };
	}
	Coord operator-(Coord other) {
		return { x - other.x, y - other.y };
	}

	std::wstring GetString() {
		return std::wstring(L"")
			+ wchar_t(L'a' + x) + wchar_t(('0' + BoardSizeX) - y);
	}
	void Print() {
		std::wcout << GetString() << wchar_t('\n');
	}
};
