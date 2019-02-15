#pragma once
#include "ChessPos.h"
#include <vector>
#define B_SIZE 8

using namespace std;

enum PieceType {W_KING = 6, W_QUEEN = 5, W_ROOK = 4, W_BISHOP = 3, W_KNIGHT = 2, W_PAWN = 1,
				B_KING = -6, B_QUEEN = -5, B_ROOK = -4, B_BISHOP = -3, B_KNIGHT = -2, B_PAWN = -1, NOTYPE = 0}; // enum: các quân cờ trong bàn cờ
enum PieceColor {BLACK = -1, NOCOLOR, WHITE}; // màu
class Piece{
protected:
	float baseVal; // giá trị của quân cờ
	PieceType type; // loại quân
	bool moved;// đã di chuyển hay chưa
	bool isValidPos(ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]); // kiểm tra vị trí quân cờ có hợp lệ không
public: 
	PieceType getType() {
		return type;
	}
	virtual vector<ChessPos> getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]); // get nước đi hợp lệ của quân cờ
	virtual bool checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]); // kiểm tra các ô mà quân cờ kiểm soát
	bool hasMoved() {  
		return moved;
	}
	void setMoved(bool moved) {
		this->moved = moved;
	}
	virtual float getVal(ChessPos pos) = 0; // lấy giá trị của quân cờ
	Piece();
	~Piece();
};

#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
