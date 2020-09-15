#pragma once
#include "SDL.h"
#include "Piece.h"
class HoldRectangle
{
public:
	HoldRectangle();
	~HoldRectangle();
	void render();
	void init();
	char getHeldPiece();
	char swapHeldPiece(char);
	void setY(int);
	void clear();
	void calculateTopLeft(int&, int&);

private:
	SDL_Rect drawRect;
	Piece heldPiece;
	SDL_Color outlineColor;
	int pieceX;
	int pieceY;
	bool hasPiece;
};

