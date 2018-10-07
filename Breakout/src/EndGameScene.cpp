#include "EndGameScene.h"

// Forward initialization of button handler
void onRestartClick();
void onExitClick();

EndGameScene::EndGameScene(){}

EndGameScene::~EndGameScene(){}

bool EndGameScene::initialize()
{
	if(!this->setBackground("background/wall_background"))
	{
		return false;
	}

	this->ui = new UI();
	this->ui->initialize("end_game_menu");
	this->ui->setButtonCallback("restart_button", &onRestartClick);
	this->ui->setButtonCallback("exit_button", &onExitClick);

	return true;
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