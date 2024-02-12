#pragma once
#include <array>
#include <deque>
#include <vector>

#include "Common.h"
#include "Position.h"
#include "Moves.h"
#include "SpecialChars.h"

class BasePiece;

template <typename T, size_t X, size_t Y>
struct array2D
{
	std::array<T, X * Y>& operator[](size_t y) {
		return *(std::array<T, X * Y>*)&data[y * X];
	}
	std::array<T, X * Y> data;
};

static struct Board
{
	Board() {
		for (int i = 0; i < BoardSizeY; i++)
			MoveHistoryWindow.push_back(L".");
	}

	BasePiece*& operator[](Coord pos) {
		return internalBoard[pos.y][pos.x];
	}

	void AddMoveToHistory(const std::wstring& s) {
		MoveHistoryWindow.pop_front();
		MoveHistoryWindow.push_back(s);
		MoveHistory.push_back(s);
	}

	bool gameIsOver = false;
	Player::Winner Winner = Player::STALEMATE;

	i8 Score[2] = { 0, 0 };
	BoardMove LastMove = BoardMove("XX","XX");
	Piece::Color PlayerToMove = Piece::White;

	struct {
		Coord coord = Coord("XX");
		BasePiece* Parent = nullptr;
	} EnPessant;
	BasePiece* Promoted = nullptr;

	array2D<BasePiece*, BoardSizeX, BoardSizeY> internalBoard = { nullptr };
	std::vector<BasePiece*> Kings;

	std::deque<std::wstring> MoveHistoryWindow;
	std::vector<std::wstring> MoveHistory;
} Board;

//array2D<BasePiece*, 8, 8> Board::internalBoard = { nullptr };
//BoardMove ChessGame::LastMove = BoardMove("XX", "XX");