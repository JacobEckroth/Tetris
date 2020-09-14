#pragma once
#include "SDL.h"
#include <string>

struct boxLocation {
	int row;
	int col;
};


class Piece
{
public:
	void render();
	void update();
	void reset();
	void setColor(SDL_Color,char);
	Piece();
	~Piece();
	boxLocation*& getBoxes() {
		return boxes;
	}
	

	void setBoxes(boxLocation*);
	char getColor() {
		return colorType;
	}
	char getType() {
		return pieceType;
	}
	SDL_Color getSDLColor() {
		return pieceColor;
	}

	boxLocation*& getCenter() {
		return centerOfPiece;
	}
	void moveRight();
	void moveLeft();
	void moveDown();
	int getRotation() {
		return rotationLevel;
	}

	
	
private:
	SDL_Color pieceColor;
	boxLocation* boxes;
	int rotationLevel;
	char colorType;
	char pieceType;
	int middleCol;

	boxLocation* centerOfPiece;
	

};

