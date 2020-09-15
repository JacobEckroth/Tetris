#pragma once
#include "Piece.h"
class nextShapesHolder
{
public:
	nextShapesHolder();
	~nextShapesHolder();
	void render();
	void init(int,int);
	char getNextPiece();
	void updateLocations();
	void resetPieces();


private:
	SDL_Rect drawRect;
	Piece nextPieces[3];
	SDL_Color outlineColor;
};

