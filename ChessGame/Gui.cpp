#include "Gui.h"
#include <Windows.h>
#include <iostream>
#include "SimpleMove.h"
#include <thread>



void Gui::drawBroad(){
	bool color = true;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			RectangleShape rectangle(Vector2f(75, 75));
			rectangle.setPosition(Vector2f(j * 75, i * 75));
			if ((i == d_oldPos.y && j == d_oldPos.x) || (i == d_newPos.y && j == d_newPos.x)) {
				rectangle.setFillColor(Color(241, 175, 0)); // tô màu 2 ô cuối cùng vừa đi
			}
			else {
				if (color) rectangle.setFillColor(Color(245, 245, 245));
				else rectangle.setFillColor(Color(105, 139, 105));
			}
			color = !color;
			window.draw(rectangle);
		}
		color = !color;
	}
}

void Gui::drawPieces(){
	Sprite * m_s = NULL;
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			Sprite * s = NULL;
			switch (broad[i][j]) {
			case PieceType::W_KING:
				s = &whitePieces[0];
				break;
			case PieceType::W_QUEEN:
				s = &whitePieces[1];
				break;
			case PieceType::W_BISHOP:
				s = &whitePieces[2];
				break;
			case PieceType::W_KNIGHT:
				s = &whitePieces[3];
				break;
			case PieceType::W_ROOK:
				s = &whitePieces[4];
				break;
			case PieceType::W_PAWN:
				s = &whitePieces[5];
				break;
			case PieceType::B_KING:
				s = &blackPieces[0];
				break;
			case PieceType::B_QUEEN:
				s = &blackPieces[1];
				break;
			case PieceType::B_BISHOP:
				s = &blackPieces[2];
				break;
			case PieceType::B_KNIGHT:
				s = &blackPieces[3];
				break;
			case PieceType::B_ROOK:
				s = &blackPieces[4];
				break;
			case PieceType::B_PAWN:
				s = &blackPieces[5];
				break;
			}
			if (s != NULL) {
				if (isMoving && i == movePos.y && j == movePos.x) m_s = s;
				else {
					s->setPosition(j * 75 + 37, i * 75 + 37);
					window.draw(*s);
				}
			}
		}
	}
	if (m_s != NULL) {
		m_s->setPosition(currentPos.x, currentPos.y);
		window.draw(*m_s);
	}
	if (promoting) {
		// xu ly hien hinh anh quan phong cap
		ChessPos pos(currentPos.x / 75, currentPos.y / 75);
		if (!chessGame->getTurn()) {
			whitePieces[1].setPosition(pos.x * 75 + 37, pos.y * 75 + 37);
			whitePieces[4].setPosition(pos.x * 75 + 37, pos.y * 75 + 112);
			whitePieces[2].setPosition(pos.x * 75 + 37, pos.y * 75 + 187);
			whitePieces[3].setPosition(pos.x * 75 + 37, pos.y * 75 + 262);
			window.draw(whitePieces[1]);
			window.draw(whitePieces[2]);
			window.draw(whitePieces[3]);
			window.draw(whitePieces[4]);
		}
		else {
			blackPieces[1].setPosition(pos.x * 75 + 37, pos.y * 75 + 37);
			blackPieces[4].setPosition(pos.x * 75 + 37, pos.y * 75 - 38);
			blackPieces[2].setPosition(pos.x * 75 + 37, pos.y * 75 - 113);
			blackPieces[3].setPosition(pos.x * 75 + 37, pos.y * 75 - 188);
			window.draw(blackPieces[1]);
			window.draw(blackPieces[2]);
			window.draw(blackPieces[3]);
			window.draw(blackPieces[4]);

		}
	}
}

void Gui::creatChessGame(bool vsCom){
	chessGame = new ChessGame();
	chessGame->getBroad(broad);
	/*turn = chessGame->getTurn();
	c_status = chessGame->getCheckStatus();*/
	this->vsCom = vsCom;
	colorCom = true; 
	isMoving = false;
	promoting = false;
	d_oldPos = ChessPos(-1, -1);
	d_newPos = ChessPos(-1, -1);
}

void Gui::drawBackGround(){
	if (background_state == 0) {
		Text text;
		text.setFont(font);
		text.setCharacterSize(30);
		text.setFillColor(Color::White);
		text.setString("Vs Computer"); // 158 29
		text.setPosition(620, 250);
		window.draw(text);
		//
		text.setString("2 Players"); // 119 29

		text.setPosition(640, 300);
		window.draw(text);
	}
	else if (background_state == 1) {
		Text text;
		text.setFont(font);
		text.setCharacterSize(30);
		text.setFillColor(Color::Red);
		//
		if (vsCom) {
			text.setString("Computer");
			text.setPosition(605, 0);
			window.draw(text);
			//
			text.setString("Player");
			text.setPosition(605, 560);
			window.draw(text);
		}
		else {
			text.setString("Player2");
			text.setPosition(605, 0);
			window.draw(text);
			//
			text.setString("Player1");
			text.setPosition(605, 560);
			window.draw(text);
		}
		
		text.setFillColor(Color::White);
		text.setString("Undo"); // 68 22
		text.setPosition(665, 200);

		window.draw(text);
		//
		text.setString("Resign"); // 82 30

		text.setPosition(660, 300);
		window.draw(text);

		//
		Text text1, text2, text3;
		text1.setFont(font);
		text2.setFont(font);
		text3.setFont(font);
		text1.setCharacterSize(20);
		text2.setCharacterSize(20);
		text3.setCharacterSize(20);
		text1.setFillColor(Color::White);
		text2.setFillColor(Color::White);
		text3.setFillColor(Color::White);
		text1.setPosition(605, 50);
		text2.setPosition(605, 100);
		text3.setPosition(605, 130);
		if (chessGame->getTurn()) text1.setString("Black thinking...");
		else text1.setString("White thinking...");
		switch (chessGame->getCheckStatus()) {
			case CheckStatus::CHECK:
				text2.setString("Check");
				break;
			case CheckStatus::CHECKMATE:
				text2.setString("Checkmate");
				if (chessGame->getTurn()) text3.setString("White win!");
				else text3.setString("Black win!");
				break;
			case CheckStatus::STALEMATE:
				text2.setString("Stalemate");
				break;
			case CheckStatus::DRAW_FMR:
				text2.setString("Draw");
				text3.setString("Fifty moves rule");
				break;
			case CheckStatus::DRAW_T:
				text2.setString("Draw");
				text3.setString("Threefold repetition");
				break;
			case CheckStatus::DRAW_IM:
				text2.setString("Draw");
				text3.setString("Insufficient material");
				break;
		}
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
	}
	
}

void Gui::computerMove(){
	
	SimpleMove nextMove = chessGame->calcNextMove();
	if (chessGame->move(nextMove)) {
		d_oldPos = nextMove.getOldPos();
		d_newPos = nextMove.getNewPos();
	}
	chessGame->getBroad(broad);
}

Gui::Gui(){
	if (texture.loadFromFile("Image/Chess_Pieces.png")) {
		for (int i = 0; i < 6; i++) {
			whitePieces[i].setTexture(texture);
			whitePieces[i].setTextureRect(IntRect(i * 75, 0, 75, 75));
			whitePieces[i].setOrigin(37, 37);
			blackPieces[i].setTexture(texture);
			blackPieces[i].setTextureRect(IntRect(i * 75, 75, 75, 75));
			blackPieces[i].setOrigin(37, 37);
		}
	}
	window.create(VideoMode(800, 600), "Chess", Style::Close);
	background_state = 0;
	font.loadFromFile("Font/BrushScriptStd.otf");
}

void Gui::run(){
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					int x = event.mouseButton.x;
					int y = event.mouseButton.y;
					if (background_state == 0) {
						if (x < 778 && x > 620 && y < 279 && y > 250) {
							background_state = 1;
							creatChessGame(true);
						}
						else if (x < 759 && x > 640 && y < 329 && y > 300) {
							background_state = 1;
							creatChessGame(false);
						}
					}
					else if (background_state == 1) {
						if (!isMoving && x < 733 && x > 665 && y < 222 && y > 200) {
							if (vsCom) {
								if (chessGame->getTurn() != colorCom) { // đánh với máy chỉ undo được khi đến lượt mình
									chessGame->undoLastMove();
									chessGame->undoLastMove();
								}
							}
							else chessGame->undoLastMove();
							SimpleMove sm = chessGame->getLastMove();
							d_oldPos = sm.getOldPos();
							d_newPos = sm.getNewPos();
							chessGame->getBroad(broad);
						}
						else if (x < 759 && x > 640 && y < 329 && y > 300) {
							delete chessGame;
							background_state = 0;
						}
						else if (promoting) {
							// xu ly bam chon quan phong cap
							ChessPos newPos(currentPos.x / 75, currentPos.y / 75);
							x = x / 75;
							y = y / 75;
							if (x < 0 || x > 7 || y < 0 || y > 7) break;
							int dy = abs(newPos.y - y);
							if (x == newPos.x && dy <= 3){
								if (dy == 0) chessGame->move(SimpleMove(movePos, newPos, QUEEN));
								else if (dy == 1) chessGame->move(SimpleMove(movePos, newPos, ROOK));
								else if (dy == 2) chessGame->move(SimpleMove(movePos, newPos, BISHOP));
								else if (dy == 3) chessGame->move(SimpleMove(movePos, newPos, KNIGHT));
								d_oldPos = movePos;
								d_newPos = newPos;
								isMoving = false;
								promoting = false;
								chessGame->getBroad(broad);
							}
						}
						else {
							x = x / 75;
							y = y / 75;
							if (x < 0 || x > 7 || y < 0 || y > 7) break;
							if (broad[y][x] != 0) {
								isMoving = true;
								movePos = ChessPos(x, y);
								currentPos.x = event.mouseButton.x;
								currentPos.y = event.mouseButton.y;
							}
						}
					}
				}
			}
			else if (isMoving && !promoting && event.type == Event::MouseMoved) {
				int x = event.mouseMove.x;
				int y = event.mouseMove.y;
				if (x < 0) x = 0;
				else if (x > 599) x = 599;
				if (y < 0) y = 0;
				else if (y > 599) y = 599;
				currentPos.x = x;
				currentPos.y = y;
			}
			else if (isMoving && event.type == Event::MouseButtonReleased) {
				isMoving = false;
				ChessPos newPos(currentPos.x / 75, currentPos.y / 75);
				if (abs(broad[movePos.y][movePos.x]) == 1 && (newPos.y == 0 || newPos.y == 7)) {
					promoting = true;
					isMoving = true;
					currentPos.x = newPos.x * 75 + 37;
					currentPos.y = newPos.y * 75 + 37;
					//if (chessGame->move(movePos, newPos, PromotePiece::QUEEN)) {
					//	chessGame->getBroad(broad);
					//	//c_status = chessGame->getCheckStatus();
					//	
					//}
				}
				else if (chessGame->move(SimpleMove(movePos,newPos))) {
					chessGame->getBroad(broad);
					d_oldPos = movePos;
					d_newPos = newPos;
					//c_status = chessGame->getCheckStatus();
			
				}
			}
		}
		window.clear(Color(85, 85, 85));
		drawBackGround();
		drawBroad();
		drawPieces();
		window.display();
		Sleep(20);
		if (background_state == 1 && vsCom && !chessGame->gameHasOver() && chessGame->getTurn() == colorCom) {
			computerMove();
			/*th = new thread(&Gui::computerMove, this);*/
		}
	}
}

Gui::~Gui(){

}
