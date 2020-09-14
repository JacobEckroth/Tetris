#include "Piece.h"
#include "Window.h"
#include "Board.h"
#include <iostream>
void Piece::render() {
	
	for (int i = 0; i < 4; i++) {
		
		


			SDL_Rect drawRect;
			drawRect.w = Box::boxWidth;
			drawRect.h = Box::boxHeight;
			drawRect.x = Board::xPos + Box::boxWidth * boxes[i].col;
			drawRect.y = Board::yPos + Box::boxHeight * boxes[i].row;
			SDL_SetRenderDrawColor(Window::renderer, pieceColor.r, pieceColor.g, pieceColor.b, pieceColor.a);
			SDL_RenderFillRect(Window::renderer, &drawRect);
		
	}
	
}

void Piece::update() {	
	moveDown();
}
void Piece::setColor(SDL_Color newColor,char colorType) {
	this->colorType = colorType;
	pieceColor.r = newColor.r;
	pieceColor.g = newColor.g;
	pieceColor.b = newColor.b;
	pieceColor.a = newColor.a;

}

void Piece::reset() {
	int choice = rand() % 7;
	switch (choice) {
	case 0:
		pieceType = 'O';
		break;
	case 1:
		pieceType = 'I';
		break;
	case 2:
		pieceType = 'L';
		break;
	case 3:
		pieceType = 'J';
		break;
	case 4:
		pieceType = 'T';
		break;
	case 5:
		pieceType = 'S';
		break;
	case 6:
		pieceType = 'Z';
		break;

	}
	
	switch (pieceType) {
	case 'I':
		setColor(Box::teal,'t');
		for (int i = 0; i < 4; i++) {
			boxes[i].row = 0;
			boxes[i].col = middleCol - 2 + i;
		}
		centerOfPiece->row = -1;	//with I it's not actually the center piece it just keeps track of the top left corner.
		centerOfPiece->col = middleCol - 2;
		break;
	case 'O':
		setColor(Box::yellow,'y');
		for (int i = 0; i < 2; i++) {
			boxes[i].row = 0;
			boxes[i].col = middleCol - 1 + i;
		}
		for (int i = 2; i < 4; i++) {
			boxes[i].row = 1;
			boxes[i].col = middleCol - 3 + i;
		}
		break;
	case 'L':
		setColor(Box::orange, 'o');
		boxes[0].row = 0;
		boxes[0].col = middleCol + 1;
		for (int i = 1; i < 4; i++) {
			boxes[i].row = 1;
			boxes[i].col = middleCol - 2 + i;
		}
		centerOfPiece->row = 1;
		centerOfPiece->col = middleCol;
		break;
	case 'J':
		setColor(Box::blue, 'b');
		boxes[0].row = 0;
		boxes[0].col = middleCol - 1;
		for (int i = 1; i < 4; i++) {
			boxes[i].row = 1;
			boxes[i].col = middleCol - 2 + i;
		}
		centerOfPiece->row = 1;
		centerOfPiece->col = middleCol;
		break;
	case 'T':
		setColor(Box::purple, 'p'); 
		boxes[0].row = 0;
		boxes[0].col = middleCol;
		centerOfPiece->row = 1;
		centerOfPiece->col = middleCol;
		for(int i = 1; i < 4; i++){
			boxes[i].row = 1;
			boxes[i].col = middleCol - 2 + i;
		}
		break;
	case 'S':
		setColor(Box::red, 'r');
		
		for (int i = 0; i < 2; i++) {
			boxes[i].row = 0;
			boxes[i].col = middleCol - 1 + i;
		}
		for (int i = 2; i < 4; i++) {
			boxes[i].row = 1;
			boxes[i].col = middleCol - 2 + i;
		}
		centerOfPiece->row = 1;
		centerOfPiece->col = middleCol;
		break;

	case 'Z':
		setColor(Box::green, 'g');
		for (int i = 0; i < 2; i++) {
			boxes[i].row = 0;
			boxes[i].col = middleCol  + i;
		}
		for (int i = 2; i < 4; i++) {
			boxes[i].row = 1;
			boxes[i].col = middleCol - 3 + i;
		}
		centerOfPiece->row = 1;
		centerOfPiece->col = middleCol;
		break;
	}
	
	
}
	




void Piece::moveRight() {
	for (int i = 0; i < 4; i++) {
		boxes[i].col++;
		
	}
	centerOfPiece->col++;
}

void Piece::moveLeft() {
	for (int i = 0; i < 4; i++) {
		boxes[i].col--;
		
	}
	centerOfPiece->col--;
}
void Piece::moveDown() {
	for (int i = 0; i < 4; i++) {
		boxes[i].row++;
		
	}
	centerOfPiece->row++;
}

Piece::Piece() {
	rotationLevel = 0;
	pieceType = 'I';
	middleCol = Board::cols / 2;
	centerOfPiece = new boxLocation();
	boxes = new boxLocation[4];

}
Piece::~Piece() {
	delete centerOfPiece;
	delete[] boxes;
}

void Piece::setBoxes(boxLocation* newLocation) {
	for (int i = 0; i < 4; i++) {
		boxes[i].row = newLocation[i].row;
		boxes[i].col = newLocation[i].col;
	}
}