#pragma once
#include <SFML/Graphics.hpp>
#include "ChessGame.h"
#include <thread>
using namespace sf;
using namespace std;
class Gui{
private:
	ChessGame * chessGame;
	PieceType broad[B_SIZE][B_SIZE];
	RenderWindow window;
	Texture texture;
	Sprite whitePieces[6]; // chứa sprite của các quân cờ (ảnh)
	Sprite blackPieces[6];

	ChessPos d_oldPos, d_newPos; // các vị trí của nước đi gần nhất
	bool isMoving;
	bool vsCom;
	bool colorCom;
	bool promoting;
	ChessPos movePos;
	Vector2i currentPos;
	/*bool buttonVsCom;
	bool buttonTwoPlayer;
	bool buttonUndo;
	bool buttonResign;*/
	int background_state;
	Font font;

	void drawBroad();
	void drawPieces();
	void creatChessGame(bool vsCom);
	void drawBackGround();
	void computerMove();
public:
	Gui();
	void run();
	~Gui();
};

