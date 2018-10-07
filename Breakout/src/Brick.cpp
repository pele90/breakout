#include "Brick.h"

Brick::Brick(){}

Brick::Brick(std::string filename) : Entity(filename) {}

Brick::~Brick(){}

bool Brick::initialize()
{
	if (this->brickType.id != "")
	{
		if (!Util::loadPng(this->getTextureFilename().c_str(), this->surface))
		{
			// LOG error
		}

		// Load sounds i guess

		if (this->brickType.hitPoints == "Infinite")
		{
			this->hitpoints = -1;
		}
		else
		{
			this->hitpoints = std::stoi(this->brickType.hitPoints);
			this->breakScore = std::stoi(this->brickType.breakScore);
		}
	}

	return true;
}

void Brick::update(float deltaTime)
{
	// LOGIC and PHYSICS
}

void Brick::render(SDL_Renderer * renderer)
{
	if (this->texture == NULL && this->interactable)
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

void Brick::setInteractable(bool value)
{
	this->interactable = value;
}

bool Brick::isInteractable() const
{
	return this->interactable;
}

int Brick::handleHit()
{
	int returnValue = -1;

	// if brick is not immortal
	if (this->hitpoints != -1)
	{
		// reduce hitpoints
		this->hitpoints--;
		returnValue = this->breakScore;

		// play sound

		// if brick health below zero
		if (this->hitpoints == 0)
		{
			// destroy brick (leave empty slot)
			this->removeTexture();
			this->interactable = false;
		}
		else
		{
			std::string damagedBrickFilename = DAMAGED_BRICK_PREFIX;
			damagedBrickFilename.append(this->brickType.id).append(DAMAGED_BRICK_SUFFIX);
			if (!Util::loadPng(damagedBrickFilename.c_str(), this->surface))
			{
				// LOG error
			}
			else
			{
				this->texture = NULL;
			}
		}
	}

	return returnValue;
}

void Brick::removeTexture()
{
	SDL_DestroyTexture(this->texture);
	this->texture = NULL;

	SDL_FreeSurface(this->surface);
	this->surface = NULL;
}