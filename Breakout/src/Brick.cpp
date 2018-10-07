#include "Brick.h"

Brick::Brick(){}

Brick::Brick(std::string filename) : Entity(filename) {}

Brick::~Brick(){}

bool Brick::initialize()
{
	if (!Util::loadPng(this->getTextureFilename().c_str(), this->surface))
	{
		// LOG error
	}

	// Load sounds i guess

	return true;
}

void Brick::update(float deltaTime)
{
	// LOGIC and PHYSICS
}

void Brick::render(SDL_Renderer * renderer)
{
	if (this->texture == NULL)
	{
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	}

	SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);
}

void Brick::destroy()
{
	SDL_DestroyTexture(this->texture);
	this->texture = NULL;

	SDL_FreeSurface(this->surface);
	this->surface = NULL;
}

void Brick::setBrickType(BrickType type)
{
	this->brickType = type;
}

void Brick::handleHit()
{
	// reduce hitpoints
	this->brickType.hitPoints--;

	// if brick health below zero
	if (this->brickType.hitPoints < 0)
	{
		// destroy brick (leave empty slot)

		// play sound

		// add score
	}
}