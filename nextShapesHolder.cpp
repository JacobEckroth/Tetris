#include "nextShapesHolder.h"
#include "Box.h"
#include "Window.h"
#include <iostream>


nextShapesHolder::nextShapesHolder() {

}

nextShapesHolder::~nextShapesHolder() {

}

void nextShapesHolder::render() {
	SDL_SetRenderDrawColor(Window::renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
	SDL_RenderDrawRect(Window::renderer, &drawRect);
	for (int i = 0; i < 3; i++) {
		nextPieces[i].render();
	}
}

void nextShapesHolder::resetPieces() {
	for (int i = 0; i < 3; i++) {
		nextPieces[i].reset(' ');
		nextPieces[i].setHeld(true);
		
		nextPieces[i].setColsToZero();
	}
}

void nextShapesHolder::init(int newX, int newY) {
	drawRect.w = 5 * Box::boxWidth;
	drawRect.h = 15 * Box::boxHeight;
	outlineColor.r = Board::gridColor.r;
	outlineColor.g = Board::gridColor.g;
	outlineColor.b = Board::gridColor.b;
	outlineColor.a = Board::gridColor.a;
	drawRect.x = newX;
	drawRect.y = newY;
	for (int i = 0; i < 3; i++) {
		nextPieces[i].reset(' ');
		nextPieces[i].setHeld(true);
	
		nextPieces[i].setColsToZero();
	}
	
	
}
char nextShapesHolder::getNextPiece() {
	char temp = nextPieces[0].getType();

	nextPieces[0].reset(nextPieces[1].getType());
	nextPieces[1].reset(nextPieces[2].getType());
	nextPieces[2].reset(' ');
	for (int i = 0; i < 3; i++) {
		nextPieces[i].setColsToZero();
	}
	
	updateLocations();
	return temp;
}

void nextShapesHolder::updateLocations() {
	
	for (int i = 0; i < 3; i++) {


		int pixelWidth = nextPieces[i].getWidth() * Box::boxWidth;
		int pixelHeight = nextPieces[i].getHeight() * Box::boxHeight;


		int horizontalCenter = drawRect.x + drawRect.w / 2;

		int verticalCenter = drawRect.y  + (5*Box::boxHeight * i)+ (5*Box::boxHeight / 2);

		int x = horizontalCenter - (pixelWidth / 2);

		int y = verticalCenter - (pixelHeight / 2);
		nextPieces[i].updateHeld(x, y);
	}

}