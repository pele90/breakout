#include "EndGameScene.h"

// Forward initialization of button handler
void onRestartClick();
void onEndGameExitClick();
void onEndGameMenuClick();

EndGameScene::EndGameScene(){}

EndGameScene::~EndGameScene(){}

bool EndGameScene::initialize()
{
	if(!this->setBackground(END_GAME_SCENE_BACKGROUND_TEXTURE_PATH))
	{
		return false;
	}

	SoundManager::addMusic(MENU_MUSIC_NAME);
	SoundManager::playMusic(MENU_MUSIC_NAME);
	SoundManager::addSound(BUTTON_CLICK_SOUND);

	this->ui = new UI();
	this->ui->initialize(END_GAME_SCENE_LAYOUT_NAME);
	this->ui->setButtonCallback(RESTART_BUTTON_NAME, &onRestartClick);
	this->ui->setButtonCallback(EXIT_BUTTON_NAME, &onEndGameExitClick);
	this->ui->setButtonCallback(MENU_BUTTON_NAME, &onEndGameMenuClick);

	//std::string message = ? VICTORY_MESSAGE : GAME_LOST_MASSAGE;
	this->ui->changeLabelText(END_GAME_SCORE_VALUE_LABEL_NAME, std::to_string(GlobalState::getScore()));


	return true;
}

// Button handlers
void onRestartClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::Restart);
	GlobalState::setScore(0);
}

void onEndGameExitClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::Exit);
}

void onEndGameMenuClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::ShowMenu);
	GlobalState::setScore(0);
}