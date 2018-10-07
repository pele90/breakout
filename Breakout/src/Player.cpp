#include "Player.h"

Player::Player() {}

Player::Player(std::string filename) : Entity(filename) {}

Player::~Player() {}

bool Player::initialize()
{
	if (!Util::loadPng(this->getTextureFilename().c_str(), this->surface))
	{
		// LOG error
		return false;
	}

	SDL_Rect rect = { 400, 650, 200, 30 };
	this->setTransform(rect);

	return true;
}

void Player::update(float deltaTime)
{
	this->move(deltaTime);
}

void Player::render(SDL_Renderer* renderer)
{
	if (this->texture == NULL)
	{
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	}

	SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);
}

void Player::destroy()
{
}

void Player::move(float deltaTime)
{
	float velocity = MOVEMENT_SPEED * deltaTime;
	if (Input::isRightArrowPressed())
	{
		if (this->transform.x <= (SCREEN_WIDTH - this->transform.w))
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