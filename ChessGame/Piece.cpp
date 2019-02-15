#include "Piece.h"



bool Piece::isValidPos(ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]){
	if (d_pos.x < 0 || d_pos.x > 7 || d_pos.y < 0 || d_pos.y > 7) return false;
	if (broad[d_pos.y][d_pos.x] == NULL || broad[d_pos.y][d_pos.x]->getType()*type < 0) return true;
	return false;
}

vector<ChessPos> Piece::getValidMoves(ChessPos pos, Piece * broad[B_SIZE][B_SIZE])
{
	return vector<ChessPos>();
}

bool Piece::checkControl(ChessPos pos, ChessPos d_pos, Piece * broad[B_SIZE][B_SIZE]){
	return false;
}

Piece::Piece(){
	type = NOTYPE;
	moved = false;
}


Piece::~Piece()
{
}
