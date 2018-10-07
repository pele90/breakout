#include "Ball.h"

Ball::Ball(){}

Ball::Ball(std::string filename) : Entity(filename){}

Ball::~Ball(){}

bool Ball::initialize()
{
	if (!Util::loadPng(this->getTextureFilename().c_str(), this->surface))
	{
		Util::showMessageBox("Loading .png failed");
		return false;
	}

	this->setTransform(BALL_STARTING_POSITION);
	this->velocity = BALL_STARTING_DIRECTION;

	return true;
}

void Ball::update(float deltaTime)
{
	if (!this->followPlayer)
	{
		this->transform.x += this->velocity.getX();
		this->transform.y += this->velocity.getY();
	}
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

void Ball::setFollowPlayer(bool value)
{
	this->followPlayer = value;
}