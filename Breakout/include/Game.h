#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "SDL.h"

#include "GlobalState.h"
#include "UI.h"
#include "SceneManager.h"
#include "Input.h"

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
