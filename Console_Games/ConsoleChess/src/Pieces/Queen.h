#pragma once
#include "BasePiece.h"

class Queen : public BasePiece
{
public:
	PieceConstructor(Queen)
	virtual bool IsValidMove(Coord end) override {
		int directionX = (currentPosition.x > end.x ? -1 : 1);
		int directionY = (currentPosition.y > end.y ? -1 : 1);
		Coord diff = currentPosition - end;

		if (diff.x * directionX == diff.y * directionY) {
			for (i8 s = 1; currentPosition.x + directionX * s != end.x; s++)
				if (Board[currentPosition + Coord(directionX * s, directionY * s)] != nullptr)
					return false;

			return true;
		}

		if (end.y == currentPosition.y) {
			for (i8 x = 1; currentPosition.x + directionX * x != end.x; x++)
				if (Board[currentPosition + Coord(directionX * x, 0)] != nullptr)
					return false;

			return true;
		}

		if (end.x == currentPosition.x) {
			for (i8 y = 1; currentPosition.y + directionY * y != end.y; y++)
				if (Board[currentPosition + Coord(0, directionY * y)] != nullptr)
					return false;

			return true;
		}

		return false;
	}
	virtual i8 Value() override { return 9; }
};