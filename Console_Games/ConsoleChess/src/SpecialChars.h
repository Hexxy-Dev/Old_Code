#pragma once
#include "Common.h"
#include <string>

enum Color : i8 {
	FgWhite = 0,
	FgBlack,
	BgWhite,
	BgBlack,
	BgWhiteHighlight,
	BgBlackHighlight
};

class Piece {
public:
	enum Type : i8 {
		NONE = 0,
		King,
		Queen,
		Rook,
		Bishop,
		Knight,
		Pawn
	};
	enum Color : i8 {
		White = ::FgWhite,
		Black = ::FgBlack
	};
};

class Player {
public:
	enum Winner : i8 {
		White = Piece::White,
		Black = Piece::Black,
		STALEMATE
	};
};

const std::wstring Colors[] = {
	L"\033[38;5;255m",
	L"\033[38;5;16m",

	L"\033[48;5;144m",
	L"\033[48;5;64m",

	L"\033[48;5;186m",
	L"\033[48;5;106m"
};

const std::wstring Pieces[2][7] = {
	{	L"  ",
		L"\u2654 ",
		L"\u2655 ",
		L"\u2656 ",
		L"\u2657 ",
		L"\u2658 ",
		L"\u2659 "
	},{ L"  ",
		L"\u265A ",
		L"\u265B ",
		L"\u265C ",
		L"\u265D ",
		L"\u265E ",
		L"\u265F "
	}
};