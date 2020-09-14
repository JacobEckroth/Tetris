#pragma once
#include "SDL.h"
class Box
{
public:
	static int boxWidth;
	static int boxHeight;
	void render();
	void updateColor(char);
	char getColor() {
		return colorType;
	}
	char getType() {
		return boxType;
	}
	Box();
	~Box();
	void init(int, int);
	bool isEmpty();

	static SDL_Color blue;
	static SDL_Color teal;
	static SDL_Color red;
	static SDL_Color orange;
	static SDL_Color yellow;
	static SDL_Color green;
	static SDL_Color purple;
	void updateType(char);
	void assignNewColor(SDL_Color);

private:
	char boxType;
	int row;
	int col;
	SDL_Color boxColor;
	char colorType;
	SDL_Rect renderRect;



};

