#include "SimpleMove.h"





SimpleMove::SimpleMove(ChessPos oldPos, ChessPos newPos, PromotePiece promoteTo){
	this->oldPos = oldPos;
	this->newPos = newPos;
	this->promoteTo = promoteTo;
}

SimpleMove::SimpleMove(ChessPos oldPos, ChessPos newPos){
	this->oldPos = oldPos;
	this->newPos = newPos;
	this->promoteTo = NON;
}

SimpleMove::~SimpleMove()
{
}
