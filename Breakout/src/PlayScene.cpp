#include "PlayScene.h"

// Forward initialization of button handler
void onReturnClick();

PlayScene::PlayScene(){}

PlayScene::~PlayScene(){}

bool PlayScene::initialize()
{
	this->setBackground("background/main_menu_background");

	this->level = new Level();
	this->level->initialize();

	this->ui = new UI();
	this->ui->initialize("game_gui");
	this->ui->setButtonCallback("continue_button", &onReturnClick);

	return true;
}

void PlayScene::update(float deltaTime)
{
	this->level->update(deltaTime);

	this->ui->update(deltaTime);
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

// Button handlers
void onReturnClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::ShowEndScreen);
}