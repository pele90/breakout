#include "SceneManager.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::initialize()
{
	this->activeScene = new MainMenuScene();
	this->activeScene->initialize();

	this->currentState = GlobalState::GameState::ShowMenu;
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
		this->activeScene->destroy();
		delete this->activeScene;

		switch (state)
		{
		case GlobalState::GameState::ShowMenu:
		{
			this->activeScene = new MainMenuScene();
			this->activeScene->initialize();
			break;
		}
		case GlobalState::GameState::Play:
		{
			this->activeScene = new PlayScene();
			this->activeScene->initialize();
			break;
		}
		case GlobalState::GameState::NextLevel:
		{
			this->activeScene = new PlayScene();
			this->activeScene->initialize();
			GlobalState::nextLevel();
			GlobalState::setCurrentState(GlobalState::GameState::Play);
			break;
		}
		case GlobalState::GameState::ShowEndScreen:
		{
			this->activeScene = new EndGameScene();
			this->activeScene->initialize();
			break;
		}
		case GlobalState::GameState::Restart:
		{
			this->activeScene = new PlayScene();
			this->activeScene->initialize();
			break;
		}
		case GlobalState::GameState::Exit:
		{
			break;
		}
		default:
			break;
		}
	}
	else
	{
		this->activeScene->update(deltaTime);
	}
}

void SceneManager::render(SDL_Renderer* renderer)
{
	this->activeScene->render(renderer);
}

void SceneManager::destroy()
{
	this->activeScene->destroy();
	delete this->activeScene;
	this->activeScene = nullptr;
}