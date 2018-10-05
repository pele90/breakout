#include "PlayScene.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

bool PlayScene::initialize()
{
	this->ui = new UI();
	this->ui->initialize("game_gui");

	return true;
}

void PlayScene::update(float deltaTime)
{
	this->ui->update(deltaTime);
}

void PlayScene::render(SDL_Renderer* renderer)
{
	this->ui->render(renderer);
}

void PlayScene::destroy()
{
	this->ui->destroy();
	this->ui = NULL;
}