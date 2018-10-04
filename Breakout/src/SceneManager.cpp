#include "SceneManager.h"

SceneManager::SceneManager(){}

SceneManager::~SceneManager(){}

void SceneManager::initialize()
{	
	this->activeScene = new MainMenuScene();
	this->activeScene->initialize();

	globalState->getInstance()->setCurrentState(GlobalState::GameState::ShowingMenu);
}

void SceneManager::update(float deltaTime)
{
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