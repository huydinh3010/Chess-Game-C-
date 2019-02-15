#pragma once
class ChessPos{
public:
	int x, y;
	ChessPos(int x, int y);
	~ChessPos();
	ChessPos();
	bool operator == (const ChessPos &pos) {
		return this->x == pos.x && this->y == pos.y;
	}
	bool operator < (const ChessPos &pos) const {
		if (y < pos.y) return true;
		if (y == pos.y && x < pos.x) return true;
		return false;
	}

};

