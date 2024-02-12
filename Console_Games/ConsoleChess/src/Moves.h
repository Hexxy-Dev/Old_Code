#pragma once
#include <algorithm>
#include <iostream>

#include "Position.h"

struct BoardMove
{
	BoardMove(std::string_view start, std::string_view end)
		: start(start), end(end)
	{}
	Coord start;
	Coord end;

	bool IsValidPosition() {
		return (start.IsValidPosition() && end.IsValidPosition() && start != end);
	}

	std::wstring GetString() {
		return std::wstring(L"")
			+ start.GetString()
			+ L" -> "
			+ end.GetString();
	}
	void Print() {
		std::wcout << GetString() << wchar_t('\n');
	}
};

BoardMove GetBasicPlayerMove() {
	while (true) {
		std::string input1, input2;
		std::cin >> input1 >> input2;

		if (input1.size() != 2 || input2.size() != 2)
			continue;

		BoardMove move(input1, input2);
		if (!move.IsValidPosition())
			continue;

		return move;
	}
}