#include "Knight.h"



vector<ChessPos> Knight::getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]){
	vector<ChessPos> listSquares;
	// di chuyển theo đường chéo hình chữ nhật 1x2
	if (isValidPos(ChessPos(pos.x + 2, pos.y + 1), broad)) listSquares.push_back(ChessPos(pos.x + 2, pos.y + 1));
	if (isValidPos(ChessPos(pos.x + 1, pos.y + 2), broad)) listSquares.push_back(ChessPos(pos.x + 1, pos.y + 2));
	if (isValidPos(ChessPos(pos.x + 1, pos.y - 2), broad)) listSquares.push_back(ChessPos(pos.x + 1, pos.y - 2));
	if (isValidPos(ChessPos(pos.x - 2, pos.y + 1), broad)) listSquares.push_back(ChessPos(pos.x - 2, pos.y + 1));
	if (isValidPos(ChessPos(pos.x - 1, pos.y + 2), broad)) listSquares.push_back(ChessPos(pos.x - 1, pos.y + 2));
	if (isValidPos(ChessPos(pos.x + 2, pos.y - 1), broad)) listSquares.push_back(ChessPos(pos.x + 2, pos.y - 1));
	if (isValidPos(ChessPos(pos.x - 2, pos.y - 1), broad)) listSquares.push_back(ChessPos(pos.x - 2, pos.y - 1));
	if (isValidPos(ChessPos(pos.x - 1, pos.y - 2), broad)) listSquares.push_back(ChessPos(pos.x - 1, pos.y - 2));
	return listSquares;
}

bool Knight::checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]){ // kiểm soát các ô nó di chuyển tới
	if (d_pos.x < 0 || d_pos.x > 7 || d_pos.y < 0 || d_pos.y > 7) return false;
	if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return false;
	if (abs(d_pos.x - pos.x) * abs(d_pos.y - pos.y) == 2) return true;
	return false;
}

float Knight::getVal(ChessPos pos) {
	if (type > 0) return baseVal + posVal[pos.y][pos.x];
	else return baseVal + posVal[7 - pos.y][7 - pos.x]; // lat nguoc lai
}

Knight::Knight(PieceColor color){
	if (color == WHITE) type = W_KNIGHT;
	else if (color == BLACK) type = B_KNIGHT;
	moved = false;
	baseVal = 30;
}


Knight::~Knight()
{
}
