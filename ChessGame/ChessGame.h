#pragma once
#include "Piece.h"
#include "Move.h"
#include "SimpleMove.h"
#include <unordered_map>
#include <set>
#include <string>
#include <stack>

using namespace std;


class ChessGame{
private:
	int depth;
	PieceType s_broad[B_SIZE][B_SIZE]; // bàn cờ dạng simple
	Piece * broad[B_SIZE][B_SIZE]; // bàn cờ đầy đủ
	int fiftyMoveRules; // biến đếm kiểm tra luật 50 nước
	bool turn; // lượt
	bool botTurn; // lượt máy
	SimpleMove bestMove; // nước đi tốt nhất
	CheckStatus c_status; // trạng thái chiếu của ván cờ
	Pawn * pawnMoveTwoSquare; // dùng để kiểm tra nước đi bắt tốt qua đường
	unordered_map<string, int> countPos; // đếm số lần xuất hiện của thế cờ
	set<ChessPos> playerPos[2]; // danh sách quân của 2 bên
	ChessPos kingPos[2]; // vị trí quân vua của 2 bên
	stack<Move *> listMoves; // danh sách nước đi
	bool gameOver;
	void clearGame();
	bool kingSafety(ChessPos oldPos, ChessPos newPos); // hàm kiểm tra quân vua có an toàn sau nước đi không
	void updateSBroad();
	CheckStatus calcCheckStatus();
	float minimax(float alpha, float beta, int depth); // thuật toán tính nước đi tốt nhất
	float eval(); // hàm lượng giá
	void t_move(SimpleMove smove);
	vector<SimpleMove> genMove(ChessPos pos); // sinh tất cả các nước đi kế tiếp
public:
	ChessGame();
	void resetGame();
	vector<ChessPos> getValidMoves(ChessPos pos); // get nước đi hợp lệ
	vector<SimpleMove> getValidSMoves(ChessPos pos);
	bool move(ChessPos oldPos, ChessPos newPos, PromotePiece promoteTo = NON); // di chuyển quân
	bool move(SimpleMove smove);
	string broadToString();
	void undoLastMove(); // đi lại nước cuối
	void getBroad(PieceType s_broad[B_SIZE][B_SIZE]);
	SimpleMove calcNextMove();
	SimpleMove getLastMove();
	CheckStatus getCheckStatus() {
		return c_status;
	}
	bool getTurn() {
		return turn;
	}
	bool gameHasOver() {
		return gameOver;
	}
	~ChessGame() {
		clearGame();
	}

};

