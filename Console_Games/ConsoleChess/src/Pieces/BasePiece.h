#pragma once
#include "../Position.h"
#include "../SpecialChars.h"
#include "../Moves.h"
#include "../Board.h"

class BasePiece
{
public:
	BasePiece() = default;

	virtual bool IsValidMove(Coord end) = 0;
	virtual i8 Value() = 0;
	virtual void Promote() { return; }
	virtual bool IsInCheck() { return false; }

	bool WillPutKingInCheck(Coord king, Coord start, Coord end, i8 friendlyCountMin) {
		if(start.IsValidPosition())
			if (Board[start])
				if (Board[start]->type == Piece::King)
					return false;

		i8 directionX = (king.x > start.x ? -1 : 1);
		i8 directionY = (king.y > start.y ? -1 : 1);
		Coord diff = king - start;

		i8 friendlyCount = 0;
		bool isDangerous = false;

		if (diff.x * directionX == diff.y * directionY)
			for (i8 s = 1; (king + Coord(directionX * s, directionY * s)).IsValidPosition() && !isDangerous; s++) {
				Coord index = king + Coord(directionX * s, directionY * s);
				Count(king, start, end, index, friendlyCount, isDangerous, Piece::Bishop);
			}

		if (start.y == king.y)
			for (i8 x = 1; (king + Coord(directionX * x, 0)).IsValidPosition() && !isDangerous; x++) {
				Coord index = king + Coord(directionX * x, 0);
				Count(king, start, end, index, friendlyCount, isDangerous, Piece::Rook);
			}

		if (start.x == king.x)
			for (i8 y = 1; (king + Coord(0, directionY * y)).IsValidPosition() && !isDangerous; y++) {
				Coord index = king + Coord(0, directionY * y);
				Count(king, start, end, index, friendlyCount, isDangerous, Piece::Rook);
			}

		if (isDangerous && friendlyCount == friendlyCountMin)
			return true;
		return false;
	}
	void Count(Coord king, Coord start, Coord end, Coord index, i8& friendlyCount, bool& isDangerous, Piece::Type secondDanger) {
		if (Board[index] != nullptr)
			if(Board[index]->color == color)
				friendlyCount++;
			else
				if (Board[index]->type == Piece::Queen || Board[index]->type == secondDanger) {
					Coord diff1 = Board[index]->currentPosition - king;
					Coord diff2 = Board[index]->currentPosition - end;
					if (!(abs(diff2.x) <= abs(diff1.x) && abs(diff2.y) <= abs(diff1.y)))
						isDangerous = true;

					if (start == end)
						isDangerous = true;
				} else
					friendlyCount++;
	}

	Coord currentPosition = Coord("XX");
	Piece::Type type = Piece::NONE;
	Piece::Color color = Piece::White;

	bool Move(BoardMove move) {
		if (Board[move.end] != nullptr)
			if (Board[move.start]->color == Board[move.end]->color)
				return false;

		if (Board.Kings[Board.PlayerToMove]->IsInCheck()) {

		}

		if (!WillPutKingInCheck(Board.Kings[Board.PlayerToMove]->currentPosition, move.start, move.end, 1)
			&& IsValidMove(move.end)) {
			if(Board[move.start]->type != Piece::Pawn)
				Board.EnPessant = { Coord("XX"), nullptr };

			if (Board[move.end] != nullptr)
				Board[move.end]->RemoveSelf();

			Board[move.end] = this;
			Board[move.start] = nullptr;

			Board.AddMoveToHistory(move.GetString());
			currentPosition = move.end;

			if (Board.Promoted)
				Board.Promoted->Promote();

			return true;
		}

		return false;
	}

	void RemoveSelf() {
		Board.Score[Board.PlayerToMove] += Value();
		Board[currentPosition] = nullptr;
		delete this;
	}

	virtual std::wstring GetString() {
		return Colors[color] + Pieces[color][type];
	}
};