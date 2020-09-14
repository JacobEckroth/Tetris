#include "Window.h"
#include "SDL.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <ctime>
#include <crtdbg.h>
int main() {
	srand(time(NULL));
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	Window* gameWindow = new Window;
	int windowWidth = 800;
	int windowHeight = 800;
	gameWindow->init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, false);
	while (gameWindow->running()) {
		frameStart = SDL_GetTicks();
		gameWindow->handleEvents();
		gameWindow->update();
		gameWindow->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	gameWindow->clean();
	delete gameWindow;




	_CrtDumpMemoryLeaks();
	return 0;
}