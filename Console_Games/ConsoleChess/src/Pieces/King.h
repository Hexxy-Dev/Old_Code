#pragma once
#include "BasePiece.h"

class King : public BasePiece
{
public:
	PieceConstructor(King)
	virtual bool IsValidMove(Coord end) override {
		if (WillBeInCheck(end))
			return false;
		Coord diff = currentPosition - end;

		if (abs(diff.x) == 1 || abs(diff.y) == 1) {
			isFirstMove = false;
			return true;
		}

		if (isFirstMove && end == currentPosition + Coord(2, 0)//Castling King Side
			&& Board[currentPosition + Coord(1, 0)] == nullptr) {
			isFirstMove = false;
			Board[currentPosition + Coord(1, 0)] = Board[currentPosition + Coord(3, 0)];
			Board[currentPosition + Coord(3, 0)] = nullptr;
			return true;
		}
		if (isFirstMove && end == currentPosition + Coord(-2, 0)//Castling Queen Side
			&& Board[currentPosition + Coord(-1, 0)] == nullptr
			&& Board[currentPosition + Coord(-3, 0)] == nullptr) {
			isFirstMove = false;
			Board[currentPosition + Coord(-1, 0)] = Board[currentPosition + Coord(-4, 0)];
			Board[currentPosition + Coord(-4, 0)] = nullptr;
			return true;
		}

		return false;
	}
	bool WillBeInCheck(Coord end) {
		return
			   WillPutKingInCheck(end, end + Coord( 0,  1), end + Coord( 0,  1), 0)
			|| WillPutKingInCheck(end, end + Coord( 0, -1), end + Coord( 0, -1), 0)
			|| WillPutKingInCheck(end, end + Coord( 1,  0), end + Coord( 1,  0), 0)
			|| WillPutKingInCheck(end, end + Coord(-1,  0), end + Coord(-1,  0), 0)
			|| WillPutKingInCheck(end, end + Coord( 1,  1), end + Coord( 1,  1), 0)
			|| WillPutKingInCheck(end, end + Coord(-1, -1), end + Coord(-1, -1), 0)
			|| WillPutKingInCheck(end, end + Coord( 1, -1), end + Coord( 1, -1), 0)
			|| WillPutKingInCheck(end, end + Coord(-1,  1), end + Coord(-1,  1), 0);
	}
	virtual bool IsInCheck() override {
		return WillBeInCheck(currentPosition);
	}
	virtual i8 Value() override { return INFINITY; /* >:3 */ }
	bool isFirstMove = true;
};