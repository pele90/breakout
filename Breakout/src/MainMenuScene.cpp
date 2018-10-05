#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
{
}

MainMenuScene::~MainMenuScene()
{
}

bool MainMenuScene::initialize()
{
	this->level = new Level();
	this->level->initialize();

	this->ui = new UI();
	this->ui->initialize("main_menu");

	return false;
}

void MainMenuScene::update(float deltaTime)
{
	this->level->update(deltaTime);

	this->ui->update(deltaTime);
}

void MainMenuScene::render(SDL_Renderer* renderer)
{
	// Render player, ball and level
	this->level->render(renderer);

	// Render UI
	this->ui->render(renderer);
}

void MainMenuScene::destroy()
{
	this->ui->destroy();
	this->ui = NULL;
}