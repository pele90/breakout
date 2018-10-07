#include "PlayScene.h"

// Forward initialization of button handler
void onReturnClick();

PlayScene::PlayScene(){}

PlayScene::~PlayScene(){}

bool PlayScene::initialize()
{
	this->setBackground("background/misc/hg14");


	this->level = new Level();

	int currentLevel = GlobalState::getLevel();
	int currentScore = GlobalState::getScore();

	std::string levelName = LEVEL_PREFIX;
	levelName.append(std::to_string(currentLevel));
	this->level->initialize(levelName);

	this->ui = new UI();
	this->ui->initialize("game_gui");
	this->ui->setButtonCallback("continue_button", &onReturnClick);
	this->ui->changeLabelText(SCORE_LABEL_NAME, std::to_string(currentScore));
	this->ui->changeLabelText(LEVEL_LABEL_NAME, std::to_string(currentLevel));

	return true;
}

void PlayScene::update(float deltaTime)
{
	// CHEAT: Q button to win
	if (Input::isQButtonPressed())
	{
		GlobalState::setCurrentState(GlobalState::GameState::NextLevel);
	}
	else
	{
		this->level->update(deltaTime);
		
		this->checkUI();
		this->ui->update(deltaTime);
	}
}

void PlayScene::render(SDL_Renderer* renderer)
{
	this->renderBackground(renderer);
	this->level->render(renderer);
	this->ui->render(renderer);
}

void PlayScene::destroy()
{
	this->level->destroy();
	delete level;
	this->level = NULL;

	this->ui->destroy();
	delete ui;
	this->ui = NULL;
}

void PlayScene::checkUI()
{
	if (this->level->isUiChanged())
	{
		this->ui->changeLabelText(SCORE_LABEL_NAME, std::to_string(GlobalState::getScore()));
		this->updateLives();

		this->level->setUiChanged(false);
	}
}

void PlayScene::updateLives()
{
	int lives = GlobalState::getLives();

	if (lives != DEFAULT_LIVES)
	{
		std::string imageName = LIVES_LABEL_NAME;
		imageName.append(std::to_string(lives + 1)); // remove current number of life + 1

		this->ui->hideImage(imageName);
	}
}

// Button handlers
void onReturnClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::ShowEndScreen);
}
