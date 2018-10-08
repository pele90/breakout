#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "SDL.h"

#include "GlobalState.h"
#include "Input.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "UI.h"

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
};

#endif // GAME_H
