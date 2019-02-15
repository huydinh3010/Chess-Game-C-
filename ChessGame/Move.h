#pragma once
#include "Piece.h"
#include "ChessPos.h"
enum class CheckStatus { NORMAL, CHECK, CHECKMATE, STALEMATE, DRAW_FMR, DRAW_T, DRAW_IM}; 
enum class TypeOfMove { NORMAL, CASTLING_KS, CASTLING_QS, ENPASSANT, PROMOTE }; // loại của nước đi
class Move {
private:
	ChessPos oldPos, newPos; // vị trí cũ, vị trí mới
	Piece * killed; // quân bị ăn
	TypeOfMove type; // loại nước đi: nhập thành, phong cấp, bắt tốt qua đường.
	int fiftyMoveRules; //
	bool firstMove;     //
	bool turn;			//				trạng thái của các biến
	CheckStatus c_status;	//
	Pawn * pawnMoveTwoSquare;//
public:
	Move(TypeOfMove type, ChessPos oldPos, ChessPos newPos, Piece * killed, Pawn * pawnMoveTwoSquare, bool firstMove, bool turn, CheckStatus c_status, int fiftyMoveRules);
	TypeOfMove getType() {
		return type;
	}
	ChessPos getOldPos() {
		return oldPos;
	}
	ChessPos getNewPos() {
		return newPos;
	}
	Piece * getKilled() {
		return killed;
	}
	Pawn * getEnPawn() {
		return pawnMoveTwoSquare;
	}
	bool getFirstMove() {
		return firstMove;
	}
	bool getTurn() {
		return turn;
	}
	CheckStatus getChecked() {
		return c_status;
	}
	int getFiftyMoveRules() {
		return fiftyMoveRules;
	}
	~Move();
};

