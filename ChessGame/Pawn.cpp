#include "Pawn.h"



vector<ChessPos> Pawn::getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE]){ 
	vector<ChessPos> listSquares;
	if (type > 0) { // trường hợp là quân trắng
		if (isValidPos(ChessPos(pos.x, pos.y - 1), broad) && broad[pos.y - 1][pos.x] == NULL) listSquares.push_back(ChessPos(pos.x, pos.y - 1)); // đi thẳng
		if (!moved && broad[pos.y - 1][pos.x] == NULL && broad[pos.y - 2][pos.x] == NULL) listSquares.push_back(ChessPos(pos.x, pos.y - 2)); //đi thẳng 2 ô ở vị trí đầu
		if (isValidPos(ChessPos(pos.x - 1, pos.y - 1), broad)) { 
			if (broad[pos.y - 1][pos.x - 1] != NULL) listSquares.push_back(ChessPos(pos.x - 1, pos.y - 1)); // ăn chéo
			else if (broad[pos.y][pos.x - 1] != NULL && broad[pos.y][pos.x - 1]->getType()*type == -1) { //  bắt tốt qua đường
				Pawn * pawn = (Pawn*)broad[pos.y][pos.x - 1];
				if (pawn->canEnpassant()) listSquares.push_back(ChessPos(pos.x - 1, pos.y - 1));
			}
		}
		if (isValidPos(ChessPos(pos.x + 1, pos.y - 1), broad)) {
			if (broad[pos.y - 1][pos.x + 1] != NULL) listSquares.push_back(ChessPos(pos.x + 1, pos.y - 1));
			else if (broad[pos.y][pos.x + 1] != NULL && broad[pos.y][pos.x + 1]->getType()*type == -1) {
				Pawn * pawn = (Pawn*)broad[pos.y][pos.x + 1];
				if (pawn->canEnpassant()) listSquares.push_back(ChessPos(pos.x + 1, pos.y - 1));
			}
		}
	}
	else if (type < 0) { // quân đen
		if (isValidPos(ChessPos(pos.x, pos.y + 1), broad) && broad[pos.y + 1][pos.x] == NULL) listSquares.push_back(ChessPos(pos.x, pos.y + 1));
		if (!moved && broad[pos.y + 1][pos.x] == NULL && broad[pos.y + 2][pos.x] == NULL) listSquares.push_back(ChessPos(pos.x, pos.y + 2));
		if (isValidPos(ChessPos(pos.x - 1, pos.y + 1), broad)) {
			if (broad[pos.y + 1][pos.x - 1] != NULL) listSquares.push_back(ChessPos(pos.x - 1, pos.y + 1));
			else if (broad[pos.y][pos.x - 1] != NULL && broad[pos.y][pos.x - 1]->getType()*type == -1) {
				Pawn * pawn = (Pawn*)broad[pos.y][pos.x - 1];
				if (pawn->canEnpassant()) listSquares.push_back(ChessPos(pos.x - 1, pos.y + 1));
			}
		}
		if (isValidPos(ChessPos(pos.x + 1, pos.y + 1), broad)) {
			if (broad[pos.y + 1][pos.x + 1] != NULL) listSquares.push_back(ChessPos(pos.x + 1, pos.y + 1));
			else if (broad[pos.y][pos.x + 1] != NULL && broad[pos.y][pos.x + 1]->getType()*type == -1) {
				Pawn * pawn = (Pawn*)broad[pos.y][pos.x + 1];
				if (pawn->canEnpassant()) listSquares.push_back(ChessPos(pos.x + 1, pos.y + 1));
			}
		}
	}
	return listSquares;
}

bool Pawn::checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]){ // kiểm soát 2 ô chéo
	if (d_pos.x < 0 || d_pos.x > 7 || d_pos.y < 0 || d_pos.y > 7) return false;
	if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return false;
	if (type > 0 && abs(d_pos.x - pos.x) == 1 && d_pos.y - pos.y == -1) return true;
	if (type < 0 && abs(d_pos.x - pos.x) == 1 && d_pos.y - pos.y == 1) return true;
	return false;
}

Pawn::Pawn(PieceColor color){
	if (color == WHITE) type = W_PAWN;
	else if (color == BLACK) type = B_PAWN;
	moved = false;
	enpassant = false;
	baseVal = 10;
}

bool Pawn::canEnpassant(){
	return enpassant;
}

void Pawn::setEnpassant(bool en){
	enpassant = en;
}

float Pawn::getVal(ChessPos pos){
	if (type > 0) return baseVal + posVal[pos.y][pos.x];
	else return baseVal + posVal[7 - pos.y][7 - pos.x]; // lat nguoc lai
}


Pawn::~Pawn()
{
}
