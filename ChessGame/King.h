#pragma once
#include "Piece.h"
class King : public Piece{
private:
	float posVal[B_SIZE][B_SIZE] = {
		{-3, -4, -4, -5, -5, -4, -4, -3},
		{-3, -4, -4, -5, -5, -4, -4, -3},
		{-3, -4, -4, -5, -5, -4, -4, -3},
		{-3, -4, -4, -5, -5, -4, -4, -3},
		{-2, -3, -3, -4, -4, -3, -3, -2},
		{-1, -2, -2, -2, -2, -2, -2, -1},
		{ 1,  0,  0,  0,  0,  0,  0,  1},
		{ 2,  3,  1,  0,  0,  1,  3,  2}
	};
public:
	vector<ChessPos> getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]);
	bool checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]);
	King(PieceColor color);
	float getVal(ChessPos pos);
	~King();
};

