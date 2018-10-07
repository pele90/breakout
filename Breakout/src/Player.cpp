#include "Player.h"

Player::Player() {}

Player::Player(std::string filename) : Entity(filename) {}

Player::~Player() {}

bool Player::initialize()
{
	if (!Util::loadPng(this->getTextureFilename().c_str(), this->surface))
	{
		Util::showMessageBox("Loading .png failed!");
		return false;
	}

	this->setTransform(PLAYER_STARTING_POSITION);

	return true;
}

void Player::update(float deltaTime)
{
	float velocity = PLAYER_MOVEMENT_SPEED * deltaTime;
	if (Input::isRightArrowPressed())
	{
		if (this->transform.x <= DEFAULT_SCREEN_WIDTH - this->transform.w)
		{
			this->transform.x += velocity;
		}
	}
	else if (Input::isLeftArrowPressed())
	{
		if (this->transform.x >= 0)
		{
			this->transform.x -= velocity;
		}
	}
}