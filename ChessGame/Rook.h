#pragma once
#include "Piece.h"
class Rook : public Piece{
private:
	float posVal[B_SIZE][B_SIZE] = {
		{   0,   0,    0,    0,    0,   0,  0,   0},
		{ 0.5,   1,    1,    1,    1,   1,  1, 0.5},
		{-0.5,   0,    0,    0,    0,   0,  0,-0.5},
		{-0.5,   0,    0,    0,    0,   0,  0,-0.5},
		{-0.5,   0,    0,    0,    0,   0,  0,-0.5},
		{-0.5,   0,    0,    0,    0,   0,  0,-0.5},
		{-0.5,   0,    0,    0,    0,   0,  0,-0.5},
		{   0,   0,    0,  0.5,  0.5,   0,  0,   0}
	};
public:
	vector<ChessPos> getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]);
	bool checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]);
	Rook(PieceColor color);
	float getVal(ChessPos pos);
	~Rook();
};

