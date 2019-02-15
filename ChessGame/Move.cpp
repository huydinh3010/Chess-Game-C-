#include "Move.h"


Move::Move(TypeOfMove type, ChessPos oldPos, ChessPos newPos, Piece * killed, Pawn * pawnMoveTwoSquare, bool firstMove, bool turn, CheckStatus c_status, int fiftyMoveRules){
	this->type = type;
	this->oldPos = oldPos;
	this->newPos = newPos;
	this->killed = killed;
	this->pawnMoveTwoSquare = pawnMoveTwoSquare;
	this->firstMove = firstMove;
	this->turn = turn;
	this->c_status = c_status;
	this->fiftyMoveRules = fiftyMoveRules;
}

Move::~Move(){
	
}
