#pragma once
#include "ChessPos.h"
enum PromotePiece { NON, QUEEN, ROOK, BISHOP, KNIGHT };
class SimpleMove{ // class biểu diễn một nước đi trong cờ vua
private:
	ChessPos oldPos, newPos; // vị trí cũ, mới
	PromotePiece promoteTo; // phong cấp thành quân gì nếu có
public:
	SimpleMove(ChessPos oldPos, ChessPos newPos, PromotePiece promoteTo);
	SimpleMove(ChessPos oldPos, ChessPos newPos);
	SimpleMove() {};
	ChessPos getOldPos() {
		return oldPos;
	}
	ChessPos getNewPos() {
		return newPos;
	}
	PromotePiece getPromotePiece() {
		return promoteTo;
	}
	~SimpleMove();
};

