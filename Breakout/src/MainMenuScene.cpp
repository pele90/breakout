#include "MainMenuScene.h"

// Forward initialization of button handler
void onPlayClick();
void onMainMenuExitClick();

MainMenuScene::MainMenuScene()
{
}

MainMenuScene::~MainMenuScene()
{
}

bool MainMenuScene::initialize()
{
	this->setBackground("background/wall_background");

	this->ui = new UI();
	this->ui->initialize("main_menu");
	this->ui->setButtonCallback("play_button", &onPlayClick);
	this->ui->setButtonCallback("exit_button", &onMainMenuExitClick);

	return true;
}

void MainMenuScene::update(float deltaTime)
{
	this->ui->update(deltaTime);
}

void MainMenuScene::render(SDL_Renderer* renderer)
{
	this->renderBackground(renderer);

	this->ui->render(renderer);
}

void MainMenuScene::destroy()
{
	this->ui->destroy();
	delete ui;
	this->ui = NULL;
}

// Button handlers
void onPlayClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::Play);
}

void onMainMenuExitClick()
{
	//GlobalState::setCurrentState(GlobalState::GameState::Exit);
}