#include "PlayScene.h"

PlayScene::PlayScene(){}

PlayScene::~PlayScene(){}

bool PlayScene::initialize()
{
	if (!this->setBackground(PLAY_SCENE_BACKGROUND_TEXTURE_PATH))
	{
		return false;
	}

	SoundManager::addMusic(GAME_MUSIC_NAME);
	SoundManager::playMusic(GAME_MUSIC_NAME);
	SoundManager::addSound(BUTTON_CLICK_SOUND);

	int currentLevel = GlobalState::getLevel();
	int currentScore = GlobalState::getScore();

	// LEVEL
	this->level = new Level();

	std::string levelName = LEVEL_PREFIX;
	levelName.append(std::to_string(currentLevel));
	this->level->initialize(levelName);

	// UI
	this->ui = new UI();
	this->ui->initialize(PLAY_SCENE_LAYOUT_NAME);
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
		this->checkUIChanges();

		Scene::update(deltaTime);
	}
}

void PlayScene::render(SDL_Renderer* renderer)
{
	Scene::render(renderer);

	this->level->render(renderer);
}

void PlayScene::destroy()
{
	this->level->destroy();
	delete level;
	this->level = nullptr;

	Scene::destroy();
}

void PlayScene::checkUIChanges()
{
	if (this->level->isUiChanged())
	{
		this->ui->changeLabelText(SCORE_LABEL_NAME, std::to_string(GlobalState::getScore()));
		this->updateLivesUI();

		this->level->setUiChanged(false);
	}
}

void PlayScene::updateLivesUI()
{
	int lives = GlobalState::getLives();

	if (lives != DEFAULT_LIVES)
	{
		std::string imageName = LIVES_LABEL_NAME;
		imageName.append(std::to_string(lives + 1)); // remove image by index; current number of life + 1

		this->ui->hideImage(imageName);
	}
}
