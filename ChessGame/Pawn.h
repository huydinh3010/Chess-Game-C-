#pragma once
#include "Piece.h"
class Pawn : public Piece{
private:
	bool enpassant; // check nước bắt tốt qua đường
	float posVal[B_SIZE][B_SIZE] = { // đánh giá giá trị của quân cờ dựa vào vị trí
			{   0,   0,    0,    0,    0,   0,   0,   0},
			{   5,   5,    5,    5,    5,   5,   5,   5},
			{   1,   1,    2,    3,    3,   2,   1,   1},
			{ 0.5, 0.5,    1,  2.5,  2.5,   1, 0.5, 0.5},
			{   0,   0,    0,    2,    2,   0,   0,   0},
			{ 0.5,-0.5,    1,    0,    0,   1,-0.5, 0.5},
			{ 0.5,   1,    1,   -2,   -2,   1,   1, 0.5},
			{   0,   0,    0,    0,    0,   0,   0,   0}
	};
public:
	vector<ChessPos> getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]);
	bool checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]);
	Pawn(PieceColor color);
	bool canEnpassant();
	void setEnpassant(bool en);
	float getVal(ChessPos pos);
	~Pawn();
};

