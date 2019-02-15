#pragma once
#include "Piece.h"
class Bishop : public Piece{
private:
	float posVal[B_SIZE][B_SIZE] = {
		{  -2,  -1,   -1,   -1,   -1,  -1,  -1,  -2},
		{  -1,   0,    0,    0,    0,   0,   0,  -1},
		{  -1,   0,  0.5,    1,    1, 0.5,   0,  -1},
		{  -1, 0.5,  0.5,    1,    1, 0.5, 0.5,-0.5},
		{  -1,   0,    1,    1,    1,   1,   0,  -1},
		{  -1,   1,    1,    1,    1,   1,   1,  -1},
		{  -1, 0.5,    0,    0,    0,   0, 0.5,  -1},
		{  -2,  -1,   -1,   -1,   -1,  -1,  -1,  -2}
	};
public:
	vector<ChessPos> getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]);
	bool checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]);
	Bishop(PieceColor color);
	float getVal(ChessPos pos);
	~Bishop();
};

