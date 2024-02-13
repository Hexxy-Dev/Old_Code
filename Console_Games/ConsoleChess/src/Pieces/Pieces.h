#pragma once

#include "BasePiece.h"

#define PieceConstructor(PIECE)				\
PIECE(Coord position, Piece::Color color) {	\
	this->currentPosition = position;		\
	this->color = color;					\
	this->type = Piece::PIECE;				\
}

#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

#undef PieceConstructor