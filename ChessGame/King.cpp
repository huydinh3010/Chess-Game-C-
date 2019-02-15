#include "King.h"
#include <cmath>
#include <iostream>

vector<ChessPos> King::getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]){
	vector<ChessPos> listSquares;
	// di chuyển trong phạm vi 1 ô
	if (isValidPos(ChessPos(pos.x + 1, pos.y + 1), broad)) listSquares.push_back(ChessPos(pos.x + 1, pos.y + 1));
	if (isValidPos(ChessPos(pos.x + 1, pos.y - 1), broad)) listSquares.push_back(ChessPos(pos.x + 1, pos.y - 1));
	if (isValidPos(ChessPos(pos.x - 1, pos.y + 1), broad)) listSquares.push_back(ChessPos(pos.x - 1, pos.y + 1));
	if (isValidPos(ChessPos(pos.x - 1, pos.y - 1), broad)) listSquares.push_back(ChessPos(pos.x - 1, pos.y - 1));
	if (isValidPos(ChessPos(pos.x + 1, pos.y), broad)) listSquares.push_back(ChessPos(pos.x + 1, pos.y));
	if (isValidPos(ChessPos(pos.x - 1, pos.y), broad)) listSquares.push_back(ChessPos(pos.x - 1, pos.y));
	if (isValidPos(ChessPos(pos.x, pos.y + 1), broad)) listSquares.push_back(ChessPos(pos.x, pos.y + 1));
	if (isValidPos(ChessPos(pos.x, pos.y - 1), broad)) listSquares.push_back(ChessPos(pos.x, pos.y - 1));
	// kiểm tra nước nhập thành
	if (!moved && broad[pos.y][pos.x + 1] == NULL && broad[pos.y][pos.x + 2] == NULL && broad[pos.y][pos.x + 3] != NULL && broad[pos.y][pos.x + 3]->getType()*type == 24 && !broad[pos.y][pos.x + 3]->hasMoved()) {
		bool b = false;
		for (int i = 0; i < B_SIZE; i++) {
			for (int j = 0; j < B_SIZE; j++) {
				if (broad[i][j] != NULL && broad[i][j]->getType()*type < 0 && 
					(broad[i][j]->checkControl(ChessPos(j, i), ChessPos(pos.x, pos.y), broad) || broad[i][j]->checkControl(ChessPos(j, i), ChessPos(pos.x + 1, pos.y), broad) || broad[i][j]->checkControl(ChessPos(j, i), ChessPos(pos.x + 2, pos.y), broad))) {
					b = true;
					break;
				}
			}
		}
		if (!b) listSquares.push_back(ChessPos(pos.x + 2, pos.y));
	}
	if (!moved && broad[pos.y][pos.x - 1] == NULL && broad[pos.y][pos.x - 2] == NULL && broad[pos.y][pos.x - 3] == NULL && broad[pos.y][pos.x - 4] != NULL && broad[pos.y][pos.x - 4]->getType()*type == 24 && !broad[pos.y][pos.x - 4]->hasMoved()) {
		bool b = false;
		for (int i = 0; i < B_SIZE; i++) {
			for (int j = 0; j < B_SIZE; j++) {
				if (broad[i][j] != NULL && broad[i][j]->getType()*type < 0 && 
					(broad[i][j]->checkControl(ChessPos(j, i), ChessPos(pos.x, pos.y), broad) || broad[i][j]->checkControl(ChessPos(j, i), ChessPos(pos.x - 1, pos.y), broad) || broad[i][j]->checkControl(ChessPos(j, i), ChessPos(pos.x - 2, pos.y), broad))) {
					b = true;
					break;
				}
			}
		}
		if (!b) listSquares.push_back(ChessPos(pos.x - 2, pos.y));
	}
	return listSquares;
}

bool King::checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]){ // kiểm soát ô liền kề
	if (d_pos.x < 0 || d_pos.x > 7 || d_pos.y < 0 || d_pos.y > 7) return false; 
	if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return false; 
	if (pow(pos.x - d_pos.x, 2) + pow(pos.y - d_pos.y, 2) <= 2) return true;
	return false;
}

float King::getVal(ChessPos pos) {
	if (type > 0) return baseVal + posVal[pos.y][pos.x];
	else return baseVal + posVal[7 - pos.y][7 - pos.x]; // lat nguoc lai
}

King::King(PieceColor color){
	if (color == WHITE) type = W_KING;
	else if (color == BLACK) type = B_KING;
	moved = false;
	baseVal = 900;
}

King::~King(){
}
