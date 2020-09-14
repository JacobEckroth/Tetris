#pragma once
#include "SDL.h"
#include "Board.h"
#undef main

#include <vector>

class Window
{
public:
	void update();
	void handleEvents();
	void clean();
	void render();
	bool running();

	Window();
	~Window();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleKeyDown(SDL_KeyboardEvent& key);
	static SDL_Renderer* renderer;
	static int screenHeight;
	static int screenWidth;
private:
	bool isRunning;
	SDL_Window* window;
	Board* board;
	
};

