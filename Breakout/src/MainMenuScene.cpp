#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
{
}

MainMenuScene::~MainMenuScene()
{
}

bool MainMenuScene::initialize()
{
	ui = new UI();
	ui->initialize("main_menu");

	return false;
}

void MainMenuScene::update(float deltaTime)
{
	ui->update(deltaTime);
}

void MainMenuScene::render(SDL_Renderer* renderer)
{
	// Render UI
	ui->render(renderer);
}

void MainMenuScene::destroy()
{
	ui->destroy();
	ui = NULL;
}