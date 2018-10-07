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

bool Brick::handleHit()
{
	// reduce hitpoints
	if (this->hitpoints != -1)
	{
		this->hitpoints--;

		// if brick health below zero
		if (this->hitpoints == 0)
		{
			// destroy brick (leave empty slot)
			this->removeTexture();
			this->interactable = false;

			// play sound

			// add score

			return true;
		}
	}

	return false;
}

void Brick::removeTexture()
{
	SDL_DestroyTexture(this->texture);
	this->texture = NULL;

	SDL_FreeSurface(this->surface);
	this->surface = NULL;
}