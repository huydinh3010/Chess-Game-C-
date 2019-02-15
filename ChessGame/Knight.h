#pragma once
#include "Piece.h"
class Knight : public Piece{
private:
	float posVal[B_SIZE][B_SIZE] = {
		{  -5,  -4,   -3,   -3,   -3,  -3,  -4,  -5},
		{  -4,  -2,    0,    0,    0,   0,  -2,  -4},
		{  -3,   0,    1,  1.5,  1.5,   1,   0,  -3},
		{  -3, 0.5,  1.5,    2,    2, 1.5, 0.5,  -3},
		{  -3,   0,  1.5,    2,    2, 1.5,   0,  -3},
		{  -3, 0.5,    1,  1.5,  1.5,   1, 0.5,  -3},
		{  -4,  -2,    0,  0.5,  0.5,   0,  -2,  -4},
		{  -5,  -4,   -3,   -3,   -3,  -3,  -4,  -5}
	};
public:
	vector<ChessPos> getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]);
	bool checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]);
	float getVal(ChessPos pos);
	Knight(PieceColor color);
	~Knight();
};

