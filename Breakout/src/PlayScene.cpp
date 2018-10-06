#include "PlayScene.h"

// Forward initialization of button handler
void onReturnClick();

PlayScene::PlayScene(){}

PlayScene::~PlayScene(){}

bool PlayScene::initialize()
{
	this->ui = new UI();
	this->ui->initialize("game_gui");
	this->ui->setButtonCallback("return_button", &onReturnClick);

	return true;
}

void PlayScene::update(float deltaTime)
{
	this->ui->update(deltaTime);
}

void PlayScene::render(SDL_Renderer* renderer)
{
	this->ui->render(renderer);
}

void PlayScene::destroy()
{
	this->ui->destroy();
	delete ui;
	this->ui = NULL;
}

// Button handlers
void onReturnClick()
{
	GlobalState::setCurrentState(GlobalState::GameState::ShowingMenu);
}