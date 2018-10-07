#include "Ball.h"

Ball::Ball(){}

Ball::Ball(std::string filename) : Entity(filename){}

Ball::~Ball(){}

bool Ball::initialize()
{
	if (!Util::loadPng(this->getTextureFilename().c_str(), this->surface))
	{
		// LOG error
	}

	SDL_Rect rect = { 450, 600, 20, 20 };
	this->setTransform(rect);

	this->velocity.setX(10);
	this->velocity.setY(-10);

	return true;
}

void Ball::update(float deltaTime)
{
	this->transform.x += (this->velocity.getX() * BALL_SPEED) * deltaTime;
	this->transform.y += (this->velocity.getY() * BALL_SPEED) * deltaTime;
}

void Ball::render(SDL_Renderer* renderer)
{
	if (this->texture == NULL)
	{
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	}

	SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);
}

void Ball::destroy()
{
	SDL_DestroyTexture(this->texture);
	this->texture = NULL;

	SDL_FreeSurface(this->surface);
	this->surface = NULL;
}

void Ball::flipXVelocity()
{
	float x = this->velocity.getX() * -1;
	this->velocity.setX(x);
}

void Ball::flipYVelocity()
{
	float y = this->velocity.getY() * -1;
	this->velocity.setX(y);
}

Vector2D Ball::getVelocity() const
{
	return this->velocity;
}

void Ball::setXVelocity(float value)
{
	this->velocity.setX(value);
}

void Ball::setYVelocity(float value)
{
	this->velocity.setY(value);
}