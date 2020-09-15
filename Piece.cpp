#include "Piece.h"
#include "Window.h"
#include "Board.h"
#include <iostream>
void Piece::render() {
	if (!(isHeld)) {
		for (int i = 0; i < 4; i++) {




			SDL_Rect drawRect;
			drawRect.w = Box::boxWidth;
			drawRect.h = Box::boxHeight;
			drawRect.x = Board::xPos + Box::boxWidth * boxes[i].col;
			drawRect.y = Board::yPos + Box::boxHeight * boxes[i].row;
			SDL_SetRenderDrawColor(Window::renderer, pieceColor.r, pieceColor.g, pieceColor.b, pieceColor.a);
			SDL_RenderFillRect(Window::renderer, &drawRect);
			SDL_SetRenderDrawColor(Window::renderer, Board::gridColor.r, Board::gridColor.g, Board::gridColor.b, Board::gridColor.a);
			SDL_RenderDrawRect(Window::renderer, &drawRect);

		}
	}
	else {
		for (int i = 0; i < 4; i++) {
		
		
			SDL_Rect drawRect;
			drawRect.w = Box::boxWidth;
			drawRect.h = Box::boxHeight;
			
			drawRect.x = heldX + Box::boxWidth * boxes[i].col;
			
			drawRect.y = heldY + Box::boxHeight * boxes[i].row;
			SDL_SetRenderDrawColor(Window::renderer, pieceColor.r, pieceColor.g, pieceColor.b, pieceColor.a);
			SDL_RenderFillRect(Window::renderer, &drawRect);
			SDL_SetRenderDrawColor(Window::renderer, Board::gridColor.r, Board::gridColor.g, Board::gridColor.b, Board::gridColor.a);
			SDL_RenderDrawRect(Window::renderer, &drawRect);


		}
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

void Piece::reset(char pieceChoice) {
	pieceType = ' ';
	if (pieceChoice == ' ') {
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
	}
	else {
		pieceType = pieceChoice;
	}
	
	switch (pieceType) {
	case 'I':
		setColor(Box::teal,'t');
		width = 4;
		height = 1;
		for (int i = 0; i < 4; i++) {
			boxes[i].row = 0;
			boxes[i].col = middleCol - 2 + i;
		}
		topLeftCorner->row = -1;	//with I it's not actually the center piece it just keeps track of the top left corner.
		topLeftCorner->col = middleCol - 2;
		break;
	case 'O':
		width = 2;
		height = 2;
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
		width = 3;
		height = 2;
		setColor(Box::orange, 'o');
		boxes[0].row = 0;
		boxes[0].col = middleCol + 1;
		for (int i = 1; i < 4; i++) {
			boxes[i].row = 1;
			boxes[i].col = middleCol - 2 + i;
		}
		topLeftCorner->row = 0;
		topLeftCorner->col = middleCol-1;
		break;
	case 'J':
		width = 3;
		height = 2;
		setColor(Box::blue, 'b');
		boxes[0].row = 0;
		boxes[0].col = middleCol - 1;
		for (int i = 1; i < 4; i++) {
			boxes[i].row = 1;
			boxes[i].col = middleCol - 2 + i;
		}
		topLeftCorner->row = 0;
		topLeftCorner->col = middleCol-1;
		break;
	case 'T':
		width = 3;
		height = 2;
		setColor(Box::purple, 'p'); 
		boxes[0].row = 0;
		boxes[0].col = middleCol;
		topLeftCorner->row = 0;
		topLeftCorner->col = middleCol-1;
		for(int i = 1; i < 4; i++){
			boxes[i].row = 1;
			boxes[i].col = middleCol - 2 + i;
		}
		break;
	case 'S':
		width = 3;
		height = 2;
		setColor(Box::red, 'r');
		
		for (int i = 0; i < 2; i++) {
			boxes[i].row = 0;
			boxes[i].col = middleCol - 1 + i;
		}
		for (int i = 2; i < 4; i++) {
			boxes[i].row = 1;
			boxes[i].col = middleCol - 2 + i;
		}
		topLeftCorner->row = 0;
		topLeftCorner->col = middleCol-1;
		break;

	case 'Z':
		width = 3;
		height = 2;
		setColor(Box::green, 'g');
		for (int i = 0; i < 2; i++) {
			boxes[i].row = 0;
			boxes[i].col = middleCol  + i;
		}
		for (int i = 2; i < 4; i++) {
			boxes[i].row = 1;
			boxes[i].col = middleCol - 3 + i;
		}
		topLeftCorner->row = 0;
		topLeftCorner->col = middleCol-1;
		break;
	}
	
	
}
	




void Piece::moveRight() {
	for (int i = 0; i < 4; i++) {
		boxes[i].col++;
		
	}
	topLeftCorner->col++;
}

void Piece::setColsToZero() {
	int lowestCol = -1;
	while (lowestCol < 0) {
		lowestCol = 100;
		for (int i = 0; i < 4; i++) {
			if (boxes[i].col < lowestCol) {
				lowestCol = boxes[i].col;
				
			}
		}
		
		if (lowestCol < 0) {
			for (int i = 0; i < 4; i++) {
				boxes[i].col++;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
	
	}
}
void Piece::moveLeft() {
	for (int i = 0; i < 4; i++) {
		boxes[i].col--;
		
	}
	topLeftCorner->col--;
}
void Piece::moveDown() {
	for (int i = 0; i < 4; i++) {
		boxes[i].row++;
		
	}
	topLeftCorner->row++;
}

Piece::Piece() {
	rotationLevel = 0;
	pieceType = 'I';
	middleCol = Board::cols / 2;
	topLeftCorner = new boxLocation();
	boxes = new boxLocation[4];
	isHeld = false;
	width = height = 0;
}
Piece::~Piece() {
	delete topLeftCorner;
	delete[] boxes;
}

void Piece::setBoxes(boxLocation* newLocation) {
	for (int i = 0; i < 4; i++) {
		boxes[i].row = newLocation[i].row;
		boxes[i].col = newLocation[i].col;
	}
}