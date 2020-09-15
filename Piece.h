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
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}


	void render();
	void update();
	void reset(char);
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

	boxLocation*& getTopLeft() {
		return topLeftCorner;
	}
	void setHeld(bool newOption) {
		isHeld = newOption;
	}
	void moveRight();
	void moveLeft();
	void moveDown();
	int getRotation() {
		return rotationLevel;
	}
	void updateHeld(int newX, int newY) {
		heldX = newX;
		heldY = newY;
	}
	void setColsToZero();

	
	
private:
	SDL_Color pieceColor;
	boxLocation* boxes;
	int rotationLevel;
	char colorType;
	char pieceType;
	int middleCol;
	bool isHeld;
	boxLocation* topLeftCorner;
	int width;
	int height;
	int heldX;
	int heldY;
	

};

