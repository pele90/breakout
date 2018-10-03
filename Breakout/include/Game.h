#ifndef GAME_H
#define GAME_H

#include <SDL.h> 
#include <iostream>

//Screen dimension constants 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
	bool isRunning;
};

#endif // GAME_H
