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
		// Don't delete active scene if current state is paused, so we can continue to play
		if (state != GlobalState::GameState::Paused && this->previousState != GlobalState::GameState::Paused)
		{
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

				if (GlobalState::nextLevel())
				{
					this->activeScene = new PlayScene();
					this->activeScene->initialize();
					GlobalState::setCurrentState(GlobalState::GameState::Play);
				}
				else
				{
					this->activeScene = new EndGameScene();
					this->activeScene->initialize();
				}

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
			case GlobalState::GameState::Paused:
			{
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

		this->currentState = state;
		this->previousState = state;
	}
	else
	{
		if (Input::isEscButtonPressed())
		{

			if (state == GlobalState::GameState::Paused)
			{
				GlobalState::setCurrentState(GlobalState::GameState::Play);
				this->activeScene->changeLabelVisibility(PLAY_PAUSE_LABEL_NAME, false);
			}
			else
			{
				if (state == GlobalState::GameState::Play)
				{
					GlobalState::setCurrentState(GlobalState::GameState::Paused);
					this->activeScene->changeLabelVisibility(PLAY_PAUSE_LABEL_NAME, true);
				}
			}
		}

		if (this->currentState != GlobalState::GameState::Paused)
		{
			this->activeScene->update(deltaTime);
		}
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