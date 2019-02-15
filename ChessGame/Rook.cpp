﻿#include "Rook.h"



vector<ChessPos> Rook::getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]){ // đi ngang/ dọc
	vector<ChessPos> listSquares;
	for (int i = pos.y + 1; i < 8; i++) {
		if (isValidPos(ChessPos(pos.x, i), broad)) listSquares.push_back(ChessPos(pos.x, i));
		if (broad[i][pos.x] != NULL) break;
	}
	for (int i = pos.y - 1; i >= 0; i--) {
		if (isValidPos(ChessPos(pos.x, i), broad)) listSquares.push_back(ChessPos(pos.x, i));
		if (broad[i][pos.x] != NULL) break;
	}
	for (int j = pos.x + 1; j < 8; j++) {
		if (isValidPos(ChessPos(j, pos.y), broad)) listSquares.push_back(ChessPos(j, pos.y));
		if (broad[pos.y][j] != NULL) break;
	}
	for (int j = pos.x - 1; j >= 0; j--) {
		if (isValidPos(ChessPos(j, pos.y), broad)) listSquares.push_back(ChessPos(j, pos.y));
		if (broad[pos.y][j] != NULL) break;
	}
	return listSquares;
}

bool Rook::checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]){ // kiểm soát ô nằm ngang / dọc
	if (d_pos.x < 0 || d_pos.x > 7 || d_pos.y < 0 || d_pos.y > 7) return false;
	if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return false;
	int dx = d_pos.x - pos.x;
	int dy = d_pos.y - pos.y;
	if (dx == 0 || dy == 0) {
		if (dx == 0 && dy > 0) {
			for (int i = pos.y + 1; i < d_pos.y; i++)
				if (broad[i][pos.x] != NULL) return false;
		}
		else if (dx == 0 && dy < 0) {
			for (int i = pos.y - 1; i > d_pos.y; i--)
				if (broad[i][pos.x] != NULL) return false;
		}
		else if (dx > 0 && dy == 0) {
			for (int j = pos.x + 1; j < d_pos.x; j++)
				if (broad[pos.y][j] != NULL) return false;
		}
		else if (dx < 0 && dy == 0) {
			for (int j = pos.x - 1; j > d_pos.x; j--)
				if (broad[pos.y][j] != NULL) return false;
		}
		return true;
	}
	return false;
}

float Rook::getVal(ChessPos pos) {
	if (type > 0) return baseVal + posVal[pos.y][pos.x];
	else return baseVal + posVal[7 - pos.y][7 - pos.x]; // lat nguoc lai
}

Rook::Rook(PieceColor color){
	if (color == WHITE) type = W_ROOK;
	else if (color == BLACK) type = B_ROOK;
	moved = false;
	baseVal = 50;
}


Rook::~Rook()
{
}
