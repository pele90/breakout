#include "SceneManager.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::initialize()
{
	this->activeScene = new MainMenuScene();
	this->activeScene->initialize();

	this->currentState = GlobalState::GameState::ShowingMenu;
	GlobalState::setCurrentState(this->currentState);
	this->previousState = this->currentState;
}

void SceneManager::update(float deltaTime)
{
	GlobalState::GameState state = GlobalState::getCurrentState();
	if (this->previousState != state)
	{
		this->currentState = state;
		this->previousState = state;

		switch (state)
		{
		case GlobalState::GameState::ShowingMenu:
		{
			this->activeScene = new MainMenuScene();
			this->activeScene->initialize();
			break;
		}
		case GlobalState::GameState::Playing:
		{
			this->activeScene = new PlayScene();
			this->activeScene->initialize();
			break;
		}

		default:
			break;
		}
	}


	this->activeScene->update(deltaTime);
}

void SceneManager::render(SDL_Renderer* renderer)
{
	this->activeScene->render(renderer);
}

void SceneManager::destroy()
{
	this->activeScene->destroy();
}

void SceneManager::switchScene(Scene* scene)
{
	this->activeScene = scene;
}