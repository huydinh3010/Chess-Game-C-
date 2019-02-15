#include "Bishop.h"



vector<ChessPos> Bishop::getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]){ // đi chéo
	vector<ChessPos> listSquares;
	for (int i = pos.y + 1, j = pos.x + 1; i < 8 && j < 8; i++, j++) {
		if (isValidPos(ChessPos(j, i), broad)) listSquares.push_back(ChessPos(j, i));
		if (broad[i][j] != NULL) break;
	}
	for (int i = pos.y + 1, j = pos.x - 1; i < 8 && j >= 0; i++, j--) {
		if (isValidPos(ChessPos(j, i), broad)) listSquares.push_back(ChessPos(j, i));
		if (broad[i][j] != NULL) break;
	}
	for (int i = pos.y - 1, j = pos.x + 1; i >= 0 && j < 8; i--, j++) {
		if (isValidPos(ChessPos(j, i), broad)) listSquares.push_back(ChessPos(j, i));
		if (broad[i][j] != NULL) break;
	}
	for (int i = pos.y - 1, j = pos.x - 1; i >= 0 && j >= 0; i--, j--) {
		if (isValidPos(ChessPos(j, i), broad)) listSquares.push_back(ChessPos(j, i));
		if (broad[i][j] != NULL) break;
	}
	return listSquares;
}

bool Bishop::checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]){ // kiểm soát các ô trên đường chéo
	if (d_pos.x < 0 || d_pos.x > 7 || d_pos.y < 0 || d_pos.y > 7) return false;
	if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return false;
	int dx = d_pos.x - pos.x;
	int dy = d_pos.y - pos.y;
	if (abs(dx) == abs(dy)) {
		if (dx > 0 && dy > 0) {
			for (int i = pos.y + 1, j = pos.x + 1; i < d_pos.y; i++, j++)
				if (broad[i][j] != NULL) return false;
		}
		else if (dx > 0 && dy < 0) {
			for (int i = pos.y - 1, j = pos.x + 1; i > d_pos.y; i--, j++)
				if (broad[i][j] != NULL) return false;
		}
		else if (dx < 0 && dy > 0) {
			for (int i = pos.y + 1, j = pos.x - 1; i < d_pos.y; i++, j--)
				if (broad[i][j] != NULL) return false;
		}
		else if (dx < 0 && dy < 0) {
			for (int i = pos.y - 1, j = pos.x - 1; i > d_pos.y; i--, j--)
				if (broad[i][j] != NULL) return false;
		}
		return true;
	}
	return false;
}

Bishop::Bishop(PieceColor color){
	if (color == WHITE) type = W_BISHOP;
	else if (color == BLACK) type = B_BISHOP;
	moved = false;
	baseVal = 30;
}

float Bishop::getVal(ChessPos pos) {
	if (type > 0) return baseVal + posVal[pos.y][pos.x];
	else return baseVal + posVal[7 - pos.y][7 - pos.x]; // lat nguoc lai
}

Bishop::~Bishop()
{
}
