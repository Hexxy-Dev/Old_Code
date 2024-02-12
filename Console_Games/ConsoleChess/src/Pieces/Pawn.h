#pragma once
#include "BasePiece.h"

class Pawn : public BasePiece
{
public:
	PieceConstructor(Pawn)
	
	bool IsValidMoveInternal(Coord end) {
		int direction = (color == Piece::White ? -1 : 1);

		if (Board[end] == nullptr) {
			if (isFirstMove && end == currentPosition + Coord(0, direction * 2)) {
				isFirstMove = false;//this will mess with the king check after!!!
				Board.EnPessant = { currentPosition + Coord(0, direction) , this };
				return true;
			}

			if (end == currentPosition + Coord(0, direction)) {
				isFirstMove = false;
				Board.EnPessant = { Coord("XX"), nullptr };
				return true;
			}
		}

		if (end == currentPosition + Coord(-1, direction)
			|| end == currentPosition + Coord(1, direction)) {
			if (Board[end] != nullptr)
				return true;

			if (end == Board.EnPessant.coord) {
				Board.EnPessant.Parent->RemoveSelf();
				Board.EnPessant = { Coord("XX"), nullptr };
				return true;
			}
		}

		return false;
	}
	virtual bool IsValidMove(Coord end) override {
		bool result = IsValidMoveInternal(end);

		if (end.y == 0 || end.y == BoardSizeY)
			Board.Promoted = this;

		return result;
	}
	virtual void Promote() override {
		std::wcout <<
			L"Promote Pawn into:\n"
			L"1:Queen (Default)\n"
			L"2:Rook\n"
			L"3:Bishop\n"
			L"4:Knight\n";
		char option;
		std::cin >> option;
		option -= '0';

		Coord index = Board.Promoted->currentPosition;

		BasePiece* newPiece;

		switch (option) {
		case 2: newPiece = new Rook(index, color); break;
		case 3: newPiece = new Bishop(index, color); break;
		case 4: newPiece = new Knight(index, color); break;
		case 1:
		default: newPiece = new Queen(index, color); break;
		}

		delete Board.Promoted;
		Board.Promoted = nullptr;

		Board[index] = newPiece;
	}
	virtual i8 Value() override { return 1; }
	virtual std::wstring GetString() override {
		return Colors[color] + Pieces[Piece::White][type];
	}
	bool isFirstMove = true;
};