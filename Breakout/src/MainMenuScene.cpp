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
	if (!this->setBackground(MAIN_MENU_SCENE_BACKGROUND_TEXTURE_PATH))
	{
		return false;
	}

	SoundManager::addMusic(MENU_MUSIC_NAME);
	SoundManager::playMusic(MENU_MUSIC_NAME);
	SoundManager::addSound(BUTTON_CLICK_SOUND);

	this->ui = new UI();
	this->ui->initialize(MAIN_MENU_SCENE_LAYOUT_NAME);
	this->ui->setButtonCallback(PLAY_BUTTON_NAME, &onPlayClick);
	this->ui->setButtonCallback(EXIT_BUTTON_NAME, &onMainMenuExitClick);

	return true;
}

// Button handlers
void onPlayClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::Play);
}

void onMainMenuExitClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::Exit);
}