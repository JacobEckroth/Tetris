#include "HoldRectangle.h"
#include "Box.h"
#include "Window.h"
#include <iostream>

void HoldRectangle::init() {

	drawRect.w = 5 * Box::boxWidth;
	drawRect.h = 5 * Box::boxHeight;
	outlineColor.r = Board::gridColor.r;
	outlineColor.g = Board::gridColor.g;
	outlineColor.b = Board::gridColor.b;
	outlineColor.a = Board::gridColor.a;
	drawRect.x = Box::boxHeight;
	
	heldPiece.setHeld(true);
	hasPiece = false;
	

}

void HoldRectangle::clear() {
	hasPiece = false;
}

void HoldRectangle::setY(int newY) {
	drawRect.y = newY;
}


void HoldRectangle::render() {
	SDL_SetRenderDrawColor(Window::renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
	SDL_RenderDrawRect(Window::renderer, &drawRect);
	if (hasPiece) {
		heldPiece.render();
	}
}

HoldRectangle::HoldRectangle() {
	

}

HoldRectangle::~HoldRectangle() {

}

char HoldRectangle::getHeldPiece() {
	return ' ';
}

char HoldRectangle::swapHeldPiece(char newPiece) {
	char tempHolder = heldPiece.getType();
	if (!hasPiece) {
		tempHolder = ' ';
	}
	heldPiece.reset(newPiece);
	int x, y;
	calculateTopLeft(x,y);
	heldPiece.updateHeld(x, y);	//uupdates the top left corner of the drawBox.
	heldPiece.setColsToZero();
	hasPiece = true;

	return tempHolder;
}

void HoldRectangle::calculateTopLeft(int& x, int& y) {
	
	int pixelWidth = heldPiece.getWidth() * Box::boxWidth;
	int pixelHeight = heldPiece.getHeight() * Box::boxHeight;
	

	int horizontalCenter = drawRect.x + drawRect.w / 2;

	int verticalCenter = drawRect.y + drawRect.h / 2;

	x = horizontalCenter - (pixelWidth / 2);
	
	y = verticalCenter - (pixelHeight / 2);

}