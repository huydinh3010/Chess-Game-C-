#include "ChessGame.h"
#include <algorithm>
#include <iostream>
#define INFINITY 9999

void ChessGame::clearGame(){
	fiftyMoveRules = 0;
	turn = false;
	gameOver = false;
	c_status = CheckStatus::NORMAL;
	pawnMoveTwoSquare = NULL;
	countPos.clear();
	set<ChessPos>::iterator it;
	for (it = playerPos[0].begin(); it != playerPos[0].end(); it++) {
		ChessPos pos = *it;
		delete broad[pos.y][pos.x];
	}
	playerPos[0].clear();
	for (it = playerPos[1].begin(); it != playerPos[1].end(); it++) {
		ChessPos pos = *it;
		delete broad[pos.y][pos.x];
	}
	playerPos[1].clear();
	kingPos[0] = ChessPos(4, 7);
	kingPos[1] = ChessPos(4, 0);
	while (!listMoves.empty()) {
		delete listMoves.top()->getKilled();
		delete listMoves.top();
		listMoves.pop();
	}
}

void ChessGame::resetGame() {
	clearGame();
	broad[7][0] = new Rook(PieceColor::WHITE);
	broad[7][7] = new Rook(PieceColor::WHITE);
	broad[7][1] = new Knight(PieceColor::WHITE);
	broad[7][6] = new Knight(PieceColor::WHITE);
	broad[7][2] = new Bishop(PieceColor::WHITE);
	broad[7][5] = new Bishop(PieceColor::WHITE);
	broad[7][3] = new Queen(PieceColor::WHITE);
	broad[7][4] = new King(PieceColor::WHITE);
	broad[0][0] = new Rook(PieceColor::BLACK);
	broad[0][7] = new Rook(PieceColor::BLACK);
	broad[0][1] = new Knight(PieceColor::BLACK);
	broad[0][6] = new Knight(PieceColor::BLACK);
	broad[0][2] = new Bishop(PieceColor::BLACK);
	broad[0][5] = new Bishop(PieceColor::BLACK);
	broad[0][3] = new Queen(PieceColor::BLACK);
	broad[0][4] = new King(PieceColor::BLACK);
	for (int i = 0; i < B_SIZE; i++) {
		broad[6][i] = new Pawn(PieceColor::WHITE);
		broad[1][i] = new Pawn(PieceColor::BLACK);
		playerPos[0].insert(ChessPos(i, 7));
		playerPos[0].insert(ChessPos(i, 6));
		playerPos[1].insert(ChessPos(i, 0));
		playerPos[1].insert(ChessPos(i, 1));
		for (int j = 2; j <= 5; j++) broad[j][i] = NULL;
	}
	updateSBroad();
}

ChessGame::ChessGame(){
	fiftyMoveRules = 0;
	turn = false;
	c_status = CheckStatus::NORMAL;
	pawnMoveTwoSquare = NULL;
	kingPos[0] = ChessPos(4, 7);
	kingPos[1] = ChessPos(4, 0);
	broad[7][0] = new Rook(PieceColor::WHITE);
	broad[7][7] = new Rook(PieceColor::WHITE);
	broad[7][1] = new Knight(PieceColor::WHITE);
	broad[7][6] = new Knight(PieceColor::WHITE);
	broad[7][2] = new Bishop(PieceColor::WHITE);
	broad[7][5] = new Bishop(PieceColor::WHITE);
	broad[7][3] = new Queen(PieceColor::WHITE);
	broad[7][4] = new King(PieceColor::WHITE);
	broad[0][0] = new Rook(PieceColor::BLACK);
	broad[0][7] = new Rook(PieceColor::BLACK);
	broad[0][1] = new Knight(PieceColor::BLACK);
	broad[0][6] = new Knight(PieceColor::BLACK);
	broad[0][2] = new Bishop(PieceColor::BLACK);
	broad[0][5] = new Bishop(PieceColor::BLACK);
	broad[0][3] = new Queen(PieceColor::BLACK);
	broad[0][4] = new King(PieceColor::BLACK);
	for (int i = 0; i < B_SIZE; i++) {
		broad[6][i] = new Pawn(PieceColor::WHITE);
		broad[1][i] = new Pawn(PieceColor::BLACK);
		playerPos[0].insert(ChessPos(i, 7));
		playerPos[0].insert(ChessPos(i, 6));
		playerPos[1].insert(ChessPos(i, 0));
		playerPos[1].insert(ChessPos(i, 1));
		for (int j = 2; j <= 5; j++) broad[j][i] = NULL;
	}
	updateSBroad();
}

void ChessGame::updateSBroad(){
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			if (broad[i][j] != NULL) s_broad[i][j] = broad[i][j]->getType();
			else s_broad[i][j] = PieceType::NOTYPE;
		}
	}
}

CheckStatus ChessGame::calcCheckStatus(){ // kiểm tra trạng thái thế cờ:
	if (fiftyMoveRules >= 50) return CheckStatus::DRAW_FMR; // hòa theo luật 50 nước
	if (countPos[broadToString()] == 3) return CheckStatus::DRAW_T; // hòa theo luật: một trạng thái xuất hiện 3 lần
	if (playerPos[turn].size() == 1 && playerPos[!turn].size() == 1) return CheckStatus::DRAW_IM; // hòa theo luật: không đủ quân để chiếu hết
	if (playerPos[turn].size() + playerPos[!turn].size() == 3) {
		set<ChessPos>::iterator it;
		if (playerPos[turn].size() == 2) it = playerPos[turn].begin();
		else it = playerPos[!turn].begin();
		ChessPos pos1 = *(it);
		it++;
		ChessPos pos2 = *(it);
		int k = s_broad[pos1.y][pos1.x] * s_broad[pos2.y][pos2.x];
		if (k == 12 || k == 18) return CheckStatus::DRAW_IM; // trường hợp còn 3 quân mà gồm vua, vua tượng hoặc vua, vua mã
	}
	ChessPos king = kingPos[turn];
	bool b = false;
	bool checked = false;
	for (set<ChessPos>::iterator it = playerPos[turn].begin(); it != playerPos[turn].end(); it++) {
		vector<ChessPos> v = getValidMoves(*it);
		if (!v.empty()) {
			b = true;
			break;
		}
	}
	for (set<ChessPos>::iterator it = playerPos[!turn].begin(); it != playerPos[!turn].end(); it++) {
		ChessPos c_p = *it;
		if (broad[c_p.y][c_p.x]->checkControl(c_p, king, broad)) {
			checked = true;
			break;
		}
	}
	if (b && !checked) return CheckStatus::NORMAL; // còn nước đi & không bị chiếu
	if (b && checked) return CheckStatus::CHECK; // còn nước đi & bị chiếu 
	if (!b && !checked) return CheckStatus::STALEMATE; // hết nước đi & không bị chiếu -> hòa
	if (!b && checked) return CheckStatus::CHECKMATE; // hết nước đi & bị chiếu -> hết cờ
}

float ChessGame::minimax(float alpha, float beta, int depth){ // thuật toán minimax sử dụng cắt tỉa alpha beta
	if (depth == 0) return eval();
	float best = -INFINITY;
	bool b = false;
	vector<ChessPos> listPieces;
	for (set<ChessPos>::iterator it = playerPos[turn].begin(); it != playerPos[turn].end(); it++) {
		listPieces.push_back(*it);
	} // lấy vị trí các quân cờ
	bool br = false;
	for (int i = listPieces.size() - 1; i >= 0; i--) { // lặp qua tất cả các quân
		vector<SimpleMove> list = genMove(listPieces.at(i));
		for (int j = 0; j < list.size(); j++) { // sinh tất cả các nước đi
			b = true;
			if (best >= beta) {
				br = true;
				break;
			}
			if (best > alpha) alpha = best;
			t_move(list.at(j)); // đi nước đi
			float value = -minimax(-beta, -alpha, depth - 1); // gọi đệ quy

			if (value > best) {
				best = value;
				if (depth == this->depth - 1) bestMove = list.at(j);
			}
			undoLastMove(); // hoàn lại nước đi
		}
		if (br) break;
	}
	if (!b) return eval();
	return best;
}

float ChessGame::eval(){ // đánh giá trị số của thế cờ
	float eval = 0;
	switch (c_status) {
	case CheckStatus::CHECK:
	case CheckStatus::NORMAL:
		// đánh giá bằng chênh lệch tổng giá trị của 2 bên
		for (set<ChessPos>::iterator it = playerPos[turn].begin(); it != playerPos[turn].end(); it++) {
			ChessPos c_p = *it;
			eval += broad[c_p.y][c_p.x]->getVal(c_p); 
		}
		for (set<ChessPos>::iterator it = playerPos[!turn].begin(); it != playerPos[!turn].end(); it++) {
			ChessPos c_p = *it;
			eval -= broad[c_p.y][c_p.x]->getVal(c_p);
			
		}
	
		break;
		case CheckStatus::CHECKMATE:
			return 1 - INFINITY;
			break;
		case CheckStatus::STALEMATE:
		case CheckStatus::DRAW_FMR:
		case CheckStatus::DRAW_IM:
		case CheckStatus::DRAW_T:
			eval = 0;
			break;
	}
	return eval;
}

void ChessGame::t_move(SimpleMove smove){ // là hàm move nhưng dùng cho thuật toán minimax, không có khâu kiểm tra nước đi hợp lệ
	ChessPos oldPos = smove.getOldPos();
	ChessPos newPos = smove.getNewPos();
	PromotePiece promoteTo = smove.getPromotePiece();
	Piece * pieceMove = broad[oldPos.y][oldPos.x];
	int dx = newPos.x - oldPos.x;
	int dy = newPos.y - oldPos.y;
	TypeOfMove type;
	Piece * killed;
	Pawn * pawnEn = pawnMoveTwoSquare;
	bool firstMove = pieceMove->hasMoved();
	int fiftyMove = fiftyMoveRules;
	if (pawnMoveTwoSquare != NULL) {
		pawnMoveTwoSquare->setEnpassant(false);
		pawnMoveTwoSquare = NULL;
	}
	if (promoteTo == PromotePiece::NON) {
		if (abs(pieceMove->getType()) == 1 && abs(dx) == 1 && abs(dy) == 1 && broad[newPos.y][newPos.x] == NULL) {
			type = TypeOfMove::ENPASSANT;
			killed = broad[oldPos.y][newPos.x];
			pieceMove->setMoved(true);
			playerPos[!turn].erase(ChessPos(newPos.x, oldPos.y));
			playerPos[turn].erase(oldPos);
			playerPos[turn].insert(newPos);
			fiftyMoveRules = 0;
			broad[newPos.y][newPos.x] = pieceMove;
			broad[oldPos.y][oldPos.x] = NULL;
			broad[oldPos.y][newPos.x] = NULL;
		}
		else if (abs(pieceMove->getType()) == 6 && dx == 2) {
			fiftyMoveRules++;
			type = TypeOfMove::CASTLING_KS;
			killed = NULL;
			pieceMove->setMoved(true);
			playerPos[turn].erase(oldPos);
			playerPos[turn].insert(newPos);
			playerPos[turn].erase(ChessPos(oldPos.x + 3, oldPos.y));
			playerPos[turn].insert(ChessPos(oldPos.x + 1, oldPos.y));
			broad[oldPos.y][oldPos.x + 3]->setMoved(true);
			kingPos[turn] = newPos;
			broad[newPos.y][newPos.x] = pieceMove;
			broad[oldPos.y][oldPos.x] = NULL;
			broad[oldPos.y][oldPos.x + 1] = broad[oldPos.y][oldPos.x + 3];
			broad[oldPos.y][oldPos.x + 3] = NULL;
		}
		else if (abs(pieceMove->getType()) == 6 && dx == -2) {
			fiftyMoveRules++;
			type = TypeOfMove::CASTLING_QS;
			killed = NULL;
			pieceMove->setMoved(true);
			playerPos[turn].erase(oldPos);
			playerPos[turn].insert(newPos);
			playerPos[turn].erase(ChessPos(oldPos.x - 4, oldPos.y));
			playerPos[turn].insert(ChessPos(oldPos.x - 1, oldPos.y));
			broad[oldPos.y][oldPos.x - 4]->setMoved(true);
			kingPos[turn] = newPos;
			broad[newPos.y][newPos.x] = pieceMove;
			broad[oldPos.y][oldPos.x] = NULL;
			broad[oldPos.y][oldPos.x - 1] = broad[oldPos.y][oldPos.x - 4];
			broad[oldPos.y][oldPos.x - 4] = NULL;
		}
		else {
			type = TypeOfMove::NORMAL;
			killed = broad[newPos.y][newPos.x];
			pieceMove->setMoved(true);
			playerPos[!turn].erase(newPos);
			playerPos[turn].erase(oldPos);
			playerPos[turn].insert(newPos);
			if (abs(pieceMove->getType()) == 1 || killed != NULL) fiftyMoveRules = 0;
			else fiftyMoveRules++;
			if (abs(pieceMove->getType()) == 6) kingPos[turn] = newPos;
			if (abs(pieceMove->getType()) == 1 && abs(dy) == 2) {
				pawnMoveTwoSquare = (Pawn*)pieceMove;
				pawnMoveTwoSquare->setEnpassant(true);
			}
			broad[newPos.y][newPos.x] = pieceMove;
			broad[oldPos.y][oldPos.x] = NULL;
		}
	}
	else {
		type = TypeOfMove::PROMOTE;
		killed = broad[newPos.y][newPos.x];
		fiftyMoveRules = 0;
		playerPos[!turn].erase(newPos);
		playerPos[turn].erase(oldPos);
		playerPos[turn].insert(newPos);
		pieceMove->setMoved(true);
		delete broad[oldPos.y][oldPos.x];
		broad[oldPos.y][oldPos.x] = NULL;
		switch (promoteTo) {
		case PromotePiece::QUEEN:
			if (!turn) broad[newPos.y][newPos.x] = new Queen(PieceColor::WHITE);
			else broad[newPos.y][newPos.x] = new Queen(PieceColor::BLACK);
			break;
		case PromotePiece::ROOK:
			if (!turn) broad[newPos.y][newPos.x] = new Rook(PieceColor::WHITE);
			else broad[newPos.y][newPos.x] = new Rook(PieceColor::BLACK);
			break;
		case PromotePiece::BISHOP:
			if (!turn) broad[newPos.y][newPos.x] = new Bishop(PieceColor::WHITE);
			else broad[newPos.y][newPos.x] = new Bishop(PieceColor::BLACK);
			break;
		case PromotePiece::KNIGHT:
			if (!turn) broad[newPos.y][newPos.x] = new Knight(PieceColor::WHITE);
			else broad[newPos.y][newPos.x] = new Knight(PieceColor::BLACK);
			break;
		}
	}
	updateSBroad();
	string str = broadToString();
	if (countPos.find(str) == countPos.end()) countPos.insert(std::make_pair(str, 1));
	else countPos[str]++;
	Move * move = new Move(type, oldPos, newPos, killed, pawnEn, firstMove, turn, c_status, fiftyMove);
	listMoves.push(move);
	
	
	turn = !turn;
	c_status = calcCheckStatus();
}

vector<SimpleMove> ChessGame::genMove(ChessPos pos){ // sinh nước đi cho thuật toán minimax
	vector<SimpleMove> listSMoves;
	if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return listSMoves;
	if ((!turn && broad[pos.y][pos.x] != NULL && broad[pos.y][pos.x]->getType() > 0) ||
		(turn && broad[pos.y][pos.x] != NULL && broad[pos.y][pos.x]->getType() < 0)) {

		vector<ChessPos> v = broad[pos.y][pos.x]->getValidMoves(pos, broad);
		for (int i = 0; i < v.size(); i++) {
			ChessPos newPos = v.at(i);
			if (kingSafety(pos, newPos)) {
				if (abs(broad[pos.y][pos.x]->getType()) == 1 && (newPos.y == 0 || newPos.y == 7)) {
					listSMoves.push_back(SimpleMove(pos, newPos, PromotePiece::QUEEN));
					listSMoves.push_back(SimpleMove(pos, newPos, PromotePiece::ROOK));
					listSMoves.push_back(SimpleMove(pos, newPos, PromotePiece::BISHOP));
					listSMoves.push_back(SimpleMove(pos, newPos, PromotePiece::KNIGHT));
				}
				else listSMoves.push_back(SimpleMove(pos, newPos));
			}
		}
	}
	return listSMoves;
}

vector<ChessPos> ChessGame::getValidMoves(ChessPos pos) {
	vector<ChessPos> listSquares;
	if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return listSquares;
	if ((!turn && broad[pos.y][pos.x] != NULL && broad[pos.y][pos.x]->getType() > 0) ||
		(turn && broad[pos.y][pos.x] != NULL && broad[pos.y][pos.x]->getType() < 0)) {

		vector<ChessPos> v = broad[pos.y][pos.x]->getValidMoves(pos, broad);
		// lấy các nước đi đúng luật của từng quân và kiểm tra sự an toàn của vua
		for (int i = 0; i < v.size(); i++) {
			if(kingSafety(pos, v.at(i))) listSquares.push_back(v.at(i));
		}
	}
	return listSquares;
}

vector<SimpleMove> ChessGame::getValidSMoves(ChessPos pos){ // giống hàm trên, chỉ khác kiểu trả về
	vector<SimpleMove> listSMoves;
	if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return listSMoves;
	if ((!turn && broad[pos.y][pos.x] != NULL && broad[pos.y][pos.x]->getType() > 0) ||
		(turn && broad[pos.y][pos.x] != NULL && broad[pos.y][pos.x]->getType() < 0)) {

		vector<ChessPos> v = broad[pos.y][pos.x]->getValidMoves(pos, broad);
		for (int i = 0; i < v.size(); i++) {
			ChessPos newPos = v.at(i);
			if (kingSafety(pos, newPos)) {
				if (abs(broad[pos.y][pos.x]->getType()) == 1 && (newPos.y == 0 || newPos.y == 7)) {
					listSMoves.push_back(SimpleMove(pos, newPos, PromotePiece::QUEEN));
					listSMoves.push_back(SimpleMove(pos, newPos, PromotePiece::ROOK));
					listSMoves.push_back(SimpleMove(pos, newPos, PromotePiece::BISHOP));
					listSMoves.push_back(SimpleMove(pos, newPos, PromotePiece::KNIGHT));
				}
				else listSMoves.push_back(SimpleMove(pos, newPos));
			}
		}
	}
	return listSMoves;
}

bool ChessGame::kingSafety(ChessPos oldPos, ChessPos newPos) {
	int dx = newPos.x - oldPos.x;
	int dy = newPos.y - oldPos.y;
	// thực hiện đi thử
	Piece * pieceMove = broad[oldPos.y][oldPos.x];
	Piece * piece1 = broad[newPos.y][newPos.x];
	Piece * piece2 = broad[oldPos.y][newPos.x];
	ChessPos king = kingPos[turn];
	if (abs(pieceMove->getType()) == 6) {
		if (abs(dx) == 2) return true;
		king = newPos;
	}

	bool enpassant = false;
	if (abs(pieceMove->getType()) == 1 && abs(dy) == 1 && abs(dx) == 1 && piece1 == NULL) {
		enpassant = true;
		broad[oldPos.y][newPos.x] = NULL;
		playerPos[!turn].erase(ChessPos(newPos.x, oldPos.y));
	}
	if (piece1 != NULL) playerPos[!turn].erase(newPos);
	broad[newPos.y][newPos.x] = pieceMove;
	broad[oldPos.y][oldPos.x] = NULL;
	// kiểm tra vua có nằm ở ô bị kiểm soát bởi đối phương không?
	bool b = true;
	for (set<ChessPos>::iterator it = playerPos[!turn].begin(); it != playerPos[!turn].end(); it++) {
		ChessPos p = *it;
		if (broad[p.y][p.x]->checkControl(p, king, broad)) {
			b = false;
			break;
		}
	}
	if (enpassant) playerPos[!turn].insert(ChessPos(newPos.x, oldPos.y));
	else if (piece1 != NULL) playerPos[!turn].insert(newPos);
	// hoàn lại nước đi thử
	broad[oldPos.y][oldPos.x] = pieceMove;
	broad[newPos.y][newPos.x] = piece1;
	broad[oldPos.y][newPos.x] = piece2;
	return b;
}

bool ChessGame::move(ChessPos oldPos, ChessPos newPos, PromotePiece promoteTo) { // hàm kiểm tra di chuyển hợp lệ và thực hiện
	if (gameOver) return false;
	vector<ChessPos> v = getValidMoves(oldPos);
	Piece * pieceMove = broad[oldPos.y][oldPos.x];
	if (find(v.begin(), v.end(), newPos) == v.end()) return false;
	if (promoteTo == PromotePiece::NON && abs(pieceMove->getType()) == 1 && (newPos.y == 0 || newPos.y == 7)) return false;
	if (promoteTo != PromotePiece::NON && (abs(pieceMove->getType()) != 1 || (newPos.y != 0 && newPos.y != 7))) return false;
	
	int dx = newPos.x - oldPos.x;
	int dy = newPos.y - oldPos.y;
	// các biến để lưu lại nước đi cho việc undo
	TypeOfMove type;
	Piece * killed;
	Pawn * pawnEn = pawnMoveTwoSquare;
	bool firstMove = pieceMove->hasMoved();
	int fiftyMove = fiftyMoveRules;
	if (pawnMoveTwoSquare != NULL) {
		pawnMoveTwoSquare->setEnpassant(false);
		pawnMoveTwoSquare = NULL;
	}
	if (promoteTo == PromotePiece::NON) { // không phải nước phong cấp
		if (abs(pieceMove->getType()) == 1 && abs(dx) == 1 && abs(dy) == 1 && broad[newPos.y][newPos.x] == NULL) {
			type = TypeOfMove::ENPASSANT;
			killed = broad[oldPos.y][newPos.x];
			pieceMove->setMoved(true);
			playerPos[!turn].erase(ChessPos(newPos.x, oldPos.y));
			playerPos[turn].erase(oldPos);
			playerPos[turn].insert(newPos);
			fiftyMoveRules = 0;
			broad[newPos.y][newPos.x] = pieceMove;
			broad[oldPos.y][oldPos.x] = NULL;
			broad[oldPos.y][newPos.x] = NULL;
		}
		else if (abs(pieceMove->getType()) == 6 && dx == 2) {
			fiftyMoveRules++;
			type = TypeOfMove::CASTLING_KS;
			killed = NULL;
			pieceMove->setMoved(true);
			playerPos[turn].erase(oldPos);
			playerPos[turn].insert(newPos);
			playerPos[turn].erase(ChessPos(oldPos.x + 3, oldPos.y));
			playerPos[turn].insert(ChessPos(oldPos.x + 1, oldPos.y));
			broad[oldPos.y][oldPos.x + 3]->setMoved(true);
			kingPos[turn] = newPos;
			broad[newPos.y][newPos.x] = pieceMove;
			broad[oldPos.y][oldPos.x] = NULL;
			broad[oldPos.y][oldPos.x + 1] = broad[oldPos.y][oldPos.x + 3];
			broad[oldPos.y][oldPos.x + 3] = NULL;
		}
		else if (abs(pieceMove->getType()) == 6 && dx == -2) {
			fiftyMoveRules++;
			type = TypeOfMove::CASTLING_QS;
			killed = NULL;
			pieceMove->setMoved(true);
			playerPos[turn].erase(oldPos);
			playerPos[turn].insert(newPos);
			playerPos[turn].erase(ChessPos(oldPos.x - 4, oldPos.y));
			playerPos[turn].insert(ChessPos(oldPos.x - 1, oldPos.y));
			broad[oldPos.y][oldPos.x - 4]->setMoved(true);
			kingPos[turn] = newPos;
			broad[newPos.y][newPos.x] = pieceMove;
			broad[oldPos.y][oldPos.x] = NULL;
			broad[oldPos.y][oldPos.x - 1] = broad[oldPos.y][oldPos.x - 4];
			broad[oldPos.y][oldPos.x - 4] = NULL;
		}
		else {
			type = TypeOfMove::NORMAL;
			killed = broad[newPos.y][newPos.x];
			pieceMove->setMoved(true);
			playerPos[!turn].erase(newPos);
			playerPos[turn].erase(oldPos);
			playerPos[turn].insert(newPos);
			if (abs(pieceMove->getType()) == 1 || killed != NULL) fiftyMoveRules = 0;
			else fiftyMoveRules++;
			if (abs(pieceMove->getType()) == 6) kingPos[turn] = newPos;
			if (abs(pieceMove->getType()) == 1 && abs(dy) == 2) {
				pawnMoveTwoSquare = (Pawn*)pieceMove;
				pawnMoveTwoSquare->setEnpassant(true);
			}
			broad[newPos.y][newPos.x] = pieceMove;
			broad[oldPos.y][oldPos.x] = NULL;
		}
	}
	else {
		type = TypeOfMove::PROMOTE;
		killed = broad[newPos.y][newPos.x];
		fiftyMoveRules = 0;
		playerPos[!turn].erase(newPos);
		playerPos[turn].erase(oldPos);
		playerPos[turn].insert(newPos);
		pieceMove->setMoved(true);
		delete broad[oldPos.y][oldPos.x];
		broad[oldPos.y][oldPos.x] = NULL;
		switch (promoteTo){
			case PromotePiece::QUEEN:
				if(!turn) broad[newPos.y][newPos.x] = new Queen(PieceColor::WHITE);
				else broad[newPos.y][newPos.x] = new Queen(PieceColor::BLACK);
				break;
			case PromotePiece::ROOK:
				if (!turn) broad[newPos.y][newPos.x] = new Rook(PieceColor::WHITE);
				else broad[newPos.y][newPos.x] = new Rook(PieceColor::BLACK);
				break;
			case PromotePiece::BISHOP:
				if (!turn) broad[newPos.y][newPos.x] = new Bishop(PieceColor::WHITE);
				else broad[newPos.y][newPos.x] = new Bishop(PieceColor::BLACK);
				break;
			case PromotePiece::KNIGHT:
				if (!turn) broad[newPos.y][newPos.x] = new Knight(PieceColor::WHITE);
				else broad[newPos.y][newPos.x] = new Knight(PieceColor::BLACK);
				break;
		}
	}
	updateSBroad();
	string str = broadToString();
	if (countPos.find(str) == countPos.end()) countPos.insert(std::make_pair(str, 1));
	else countPos[str]++; // đếm số lần của thế cờ này
	Move * move = new Move(type, oldPos, newPos, killed, pawnEn, firstMove, turn, c_status, fiftyMove);
	listMoves.push(move);// lưu lại move
	
	turn = !turn;
	c_status = calcCheckStatus(); // tính toán chiếu, chiếu hết
	if (c_status != CheckStatus::NORMAL && c_status != CheckStatus::CHECK) gameOver = true;
 	return true;
}

bool ChessGame::move(SimpleMove smove){
	return move(smove.getOldPos(), smove.getNewPos(), smove.getPromotePiece());
}

string ChessGame::broadToString(){
	string str = "";
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			str += std::to_string((int)s_broad[i][j]);
		}
	}
	return str;
}

void ChessGame::undoLastMove(){ // thực hiện các bước ngược với hàm di chuyển
	if (listMoves.empty()) return;
	Move * lastMove = listMoves.top();
	fiftyMoveRules = lastMove->getFiftyMoveRules();
	c_status = lastMove->getChecked();
	ChessPos oldPos = lastMove->getOldPos();
	ChessPos newPos = lastMove->getNewPos();
	Piece * killed = lastMove->getKilled();
	Piece * pieceMove = broad[newPos.y][newPos.x];
	pieceMove->setMoved(lastMove->getFirstMove());
	turn = lastMove->getTurn();
	if (pawnMoveTwoSquare != NULL) pawnMoveTwoSquare->setEnpassant(false);
	pawnMoveTwoSquare = lastMove->getEnPawn();
	if(pawnMoveTwoSquare != NULL) pawnMoveTwoSquare->setEnpassant(true);
	countPos[broadToString()]--;
	switch (lastMove->getType()){
		case TypeOfMove::NORMAL:
			broad[oldPos.y][oldPos.x] = pieceMove;
			broad[newPos.y][newPos.x] = killed;
			if (killed != NULL) playerPos[!turn].insert(newPos);
			playerPos[turn].erase(newPos);
			playerPos[turn].insert(oldPos);
			if (abs(pieceMove->getType()) == 6) kingPos[turn] = oldPos;
			break;
		case TypeOfMove::CASTLING_KS:
			broad[oldPos.y][oldPos.x] = pieceMove;
			broad[newPos.y][newPos.x] = NULL;
			broad[oldPos.y][oldPos.x + 3] = broad[oldPos.y][oldPos.x + 1];
			broad[oldPos.y][oldPos.x + 1] = NULL;
			broad[oldPos.y][oldPos.x + 3]->setMoved(false);
			kingPos[turn] = oldPos;
			playerPos[turn].erase(newPos);
			playerPos[turn].insert(oldPos);
			playerPos[turn].erase(ChessPos(oldPos.x + 1, oldPos.y));
			playerPos[turn].insert(ChessPos(oldPos.x + 3, oldPos.y));
			break;
		case TypeOfMove::CASTLING_QS:
			broad[oldPos.y][oldPos.x] = pieceMove;
			broad[newPos.y][newPos.x] = NULL;
			broad[oldPos.y][oldPos.x - 4] = broad[oldPos.y][oldPos.x - 1];
			broad[oldPos.y][oldPos.x - 1] = NULL;
			broad[oldPos.y][oldPos.x - 4]->setMoved(false);
			kingPos[turn] = oldPos;
			playerPos[turn].erase(newPos);
			playerPos[turn].insert(oldPos);
			playerPos[turn].erase(ChessPos(oldPos.x - 1, oldPos.y));
			playerPos[turn].insert(ChessPos(oldPos.x - 4, oldPos.y));
			break;
		case TypeOfMove::ENPASSANT:
			broad[oldPos.y][oldPos.x] = pieceMove;
			broad[newPos.y][newPos.x] = NULL;
			broad[oldPos.y][newPos.x] = killed;
			playerPos[!turn].insert(ChessPos(newPos.x, oldPos.y));
			playerPos[turn].erase(newPos);
			playerPos[turn].insert(oldPos);
			break;
		case TypeOfMove::PROMOTE:
			if (!turn) broad[oldPos.y][oldPos.x] = new Pawn(WHITE);
			else broad[oldPos.y][oldPos.x] = new Pawn(BLACK);
			broad[oldPos.y][oldPos.x]->setMoved(true);
			delete pieceMove;
			broad[newPos.y][newPos.x] = killed;
			playerPos[turn].erase(newPos);
			playerPos[turn].insert(oldPos);
			if (killed != NULL) playerPos[!turn].insert(newPos);
			break;
	}
	updateSBroad();
	delete lastMove;
	listMoves.pop();
	gameOver = false;
}

void ChessGame::getBroad(PieceType s_broad[B_SIZE][B_SIZE]){
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			s_broad[i][j] = this->s_broad[i][j];
		}
	}
}

SimpleMove ChessGame::calcNextMove() {
	depth = 3;
	if (playerPos[turn].size() + playerPos[!turn].size() <= 13) depth = 4;
	else if (playerPos[turn].size() + playerPos[!turn].size() <= 10) depth = 6;
	else if (playerPos[turn].size() + playerPos[!turn].size() <= 8) depth = 7;
	else if (playerPos[turn].size() + playerPos[!turn].size() <= 6) depth = 8;
	else if (playerPos[turn].size() + playerPos[!turn].size() <= 4) depth = 9;
	else if (playerPos[turn].size() + playerPos[!turn].size() <= 3) depth = 10;
	botTurn = turn;
	minimax(-INFINITY, INFINITY, depth-1);
	return bestMove;
}

SimpleMove ChessGame::getLastMove(){
	if (!listMoves.empty()) {
		Move * move = listMoves.top();
		return SimpleMove(move->getOldPos(), move->getNewPos());
	}
	else return SimpleMove(ChessPos(-1, -1), ChessPos(-1, -1));
}
