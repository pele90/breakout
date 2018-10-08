#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "EndGameScene.h"
#include "GlobalState.h"
#include "MainMenuScene.h"
#include "PlayScene.h"
#include "Scene.h"
#include "SoundManager.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void initialize();
	void update(float deltaTime);
	void render(SDL_Renderer* renderer);
	void destroy();

private:
	Scene* activeScene;
	GlobalState::GameState currentState;
	GlobalState::GameState previousState;
};

#endif // !SCENE_MANAGER_H
