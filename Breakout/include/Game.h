#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "SDL.h"

#include "UI.h"
#include "SceneManager.h"
#include "Input.h"


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
	void run();
	void update(float deltaTime);
	void render();
	void destroy();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SceneManager* sceneManager;
	bool isRunning;

};

#endif // GAME_H
