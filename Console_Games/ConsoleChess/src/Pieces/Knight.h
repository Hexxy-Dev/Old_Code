#pragma once
#include "BasePiece.h"

class Knight : public BasePiece
{
public:
	PieceConstructor(Knight)
	virtual bool IsValidMove(Coord end) override {
		Coord diff = currentPosition - end;

		if (abs(diff.x) == 2 && abs(diff.y) == 1
		|| abs(diff.x) == 1 && abs(diff.y) == 2)
			return true;

		return false;
	}
	virtual i8 Value() override { return 3; }
};