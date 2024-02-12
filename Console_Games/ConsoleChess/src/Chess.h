#pragma once
#include "Position.h"
#include "Moves.h"
#include "Board.h"
#include "Pieces/Pieces.h"
#include "WindowsBS.h"
#include "SpecialChars.h"

static class ChessGame
{
public:
	ChessGame() {
		GetNiceConsole();

#define Create(PIECE,POS,COLOR) Board[Coord##POS] = new PIECE(Coord##POS,COLOR)
		auto CreateSet = [](i8 XOffset, i8 YOffset, i8 Direction, Piece::Color color) {
			for (int x = 0; x < 8; x++)
				Create(Pawn, (XOffset + x, YOffset + Direction), color);
			Create(Rook, (XOffset + 0, YOffset), color);
			Create(Rook, (XOffset + 7, YOffset), color);
			Create(Knight, (XOffset + 1, YOffset), color);
			Create(Knight, (XOffset + 6, YOffset), color);
			Create(Bishop, (XOffset + 2, YOffset), color);
			Create(Bishop, (XOffset + 5, YOffset), color);
			Create(Queen, (XOffset + 3, YOffset), color);
			Create(King, (XOffset + 4, YOffset), color);
			Board.Kings.push_back(Board[{XOffset + 4, YOffset}]);
		};
#undef Create

		CreateSet(0, 7, -1, Piece::White);
		CreateSet(0, 0, 1, Piece::Black);
	}
	void Display() {
		ClearScreen();

		i8 mnS = std::min(Board.Score[Piece::White], Board.Score[Piece::Black]);
		std::wstring output =
			L"  W: " + std::to_wstring(Board.Score[Piece::White] - mnS)
			+ L"   " + (Board.Score[Piece::White] < 10 ? L" " : L"")
			+ L"B: " + std::to_wstring(Board.Score[Piece::Black] - mnS)
			+ L"\n";

		for (int y = 0; y < BoardSizeY; y++) {
			output += std::to_wstring(BoardSizeY-y);

			for (int x = 0; x < BoardSizeX; x++) {
				Coord index(x, y);

				if (index == Board.LastMove.start || index == Board.LastMove.end)
					if ((x + y) % 2 == 0)
						output += Colors[Color::BgWhiteHighlight];
					else
						output += Colors[Color::BgBlackHighlight];
				else
					if ((x + y) % 2 == 0)
						output += Colors[Color::BgWhite];
					else
						output += Colors[Color::BgBlack];

				if (Board[index] == nullptr) {
					output += L"  ";
					continue;
				}
				output += Board[index]->GetString();
			}
			output += L"\033[0m          " + Board.MoveHistoryWindow[y] + L"\n";
		}
		output += L"\033[0m A B C D E F G H\n";
		std::wcout << output;
	}

	void GameOver() {
		Display();

		std::wstring output;

		if (Board.Winner == Player::STALEMATE)
			output = L"STALEMAE\n";
		else {
			output = (Board.Winner == Player::White ? L"White" : L"Black");
			output += L" Wins!!\n";
		}
		std::wcout << output;

		std::cin.get(); std::cin.get();
		output = L"Game History:\n";

		for (int i = 0; i < Board.MoveHistory.size(); i++)
			output += Board.MoveHistory[i] + L"\n";

		std::wcout << output;
	}

	void LocalPVP() {
		while (!Board.gameIsOver) {
			bool playedValidMove = false;
			BoardMove move("XX","XX");

			while (!playedValidMove) {
				Display();

				std::wcout << (Board.PlayerToMove == Piece::White ? "White" : "Black")
					<< " To Move: ";

				move = GetBasicPlayerMove();

				if(Board[move.start] != nullptr)
					//if (Board[move.start]->color == Board.PlayerToMove)
						playedValidMove = Board[move.start]->Move(move);
			}

			Board.PlayerToMove = (Board.PlayerToMove == Piece::White ?
														Piece::Black : Piece::White);
			Board.LastMove = move;
		}
		GameOver();
	}

	void Play() {
		RETRY:
		char mode = '0';

		std::wcout <<
			"Select game mode:\n"
			"1:Local PVP\n"
			"2:PVP\n"
			"3:VS AI\n\n";
		std::cin >> mode;

		switch (mode) {
		case '1': LocalPVP(); break;
		case '2': std::wcout << "WIP"; break;
		case '3': std::wcout << "WIP"; break;
		default:
			ClearScreen();
			std::wcout << "INVALID MODE SELECTED\n\n";
			goto RETRY;
		}
	}
} ChessGame;