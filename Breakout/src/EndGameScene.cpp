#include "EndGameScene.h"

// Forward initialization of button handler
void onRestartClick();
void onExitClick();

EndGameScene::EndGameScene(){}

EndGameScene::~EndGameScene(){}

bool EndGameScene::initialize()
{
	this->ui = new UI();
	this->ui->initialize("end_game_menu");
	this->ui->setButtonCallback("restart_button", &onRestartClick);
	this->ui->setButtonCallback("exit_button", &onExitClick);

	return true;
}

void EndGameScene::update(float deltaTime)
{
	this->ui->update(deltaTime);
}

void EndGameScene::render(SDL_Renderer* renderer)
{
	this->ui->render(renderer);
}

void EndGameScene::destroy()
{
	this->ui->destroy();
	delete ui;
	this->ui = NULL;
}

// Button handlers
void onRestartClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::Restart);
}

void onExitClick()
{
	//GlobalState::setCurrentState(GlobalState::GameState::Exit);
	GlobalState::setCurrentState(GlobalState::GameState::ShowMenu);
}