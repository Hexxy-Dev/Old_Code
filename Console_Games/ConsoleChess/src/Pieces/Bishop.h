#pragma once
#include "BasePiece.h"

class Bishop : public BasePiece
{
public:
	PieceConstructor(Bishop)
	virtual bool IsValidMove(Coord end) override {
		int directionX = (currentPosition.x > end.x ? -1 : 1);
		int directionY = (currentPosition.y > end.y ? -1 : 1);
		Coord diff = currentPosition - end;

		if (diff.x * directionX != diff.y * directionY)
			return false;

		for (i8 s = 1; currentPosition.x + directionX * s != end.x; s++)
			if (Board[currentPosition + Coord(directionX * s, directionY * s)] != nullptr)
				return false;

		return true;
	}
	virtual i8 Value() override { return 3; }
};