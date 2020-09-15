#include "Box.h"
#include "Window.h"
#include "Board.h"
#include <iostream>
int Box::boxWidth = 0;
int Box::boxHeight = 0;
SDL_Color Box::blue;
SDL_Color Box::teal;
SDL_Color Box::red;
SDL_Color Box::orange;
SDL_Color Box::yellow;
SDL_Color Box::green;
SDL_Color Box::purple;


bool Box::isEmpty() {
	if (boxType == 'e') {
		return true;
	}
	return false;
}


void Box::render() {
	if (boxType == 'e') {
		return;
	}
	else if (boxType == 'f') {	//is full and placed square
		
		SDL_SetRenderDrawColor(Window:: renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);
		SDL_RenderFillRect(Window::renderer, &renderRect);
	}
}

Box::Box() {

}

Box::~Box() {

}

void Box::init(int row, int col) {
	this->row = row;
	this->col = col;
	renderRect.w = Box::boxWidth;
	renderRect.h = Box::boxHeight;
	renderRect.x = Board::xPos + col * boxWidth;
	renderRect.y = Board::yPos + row * boxHeight;
	boxColor.r = 255;
	boxColor.g = boxColor.b = 0;
	boxColor.a = 255;
	colorType = ' ';
	boxType = 'e';
	

}
void Box::updateType(char newType) {
	boxType = newType;
}
void Box::updateColor(char newColor) {
	colorType = newColor;

	switch (newColor) {
	case 't':
		assignNewColor(teal);
		break;
	case 'b':
		assignNewColor(blue);
		break;
	case 'r':
		assignNewColor(red);
		break;
	case 'o':
		assignNewColor(orange);
		break;
	case 'y':
		assignNewColor(yellow);
		break;
	case 'g':
		assignNewColor(green);
		break;
	case 'p':
		assignNewColor(purple);
		break;
	case ' ':
		break;
	default:
		break;
	}
}

void Box::assignNewColor(SDL_Color newColor) {
	
	boxColor.r = newColor.r;
	
	boxColor.g = newColor.g;
	boxColor.b = newColor.b;
	
	boxColor.a = newColor.a;
}