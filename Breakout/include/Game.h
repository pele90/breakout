#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "GameGUI.h"

#include <SDL.h>

//Screen dimension constants 
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / FPS;

class Game
{
public:
	Game();
	~Game();
	bool initialize();
	void start();
	void update(float deltaTime);
	void render();
	void destroy();

private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	GameGUI* gameGUI;
	bool isRunning;

};

#endif // GAME_H
