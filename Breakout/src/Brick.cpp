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
			Util::showMessageBox("Loading .png failed");
			return false;
		}

		if (this->brickType.hitPoints == "Infinite")
		{
			this->hitpoints = -1;
		}
		else
		{
			// Converting to int here so BrickType is cleaner to work with
			this->hitpoints = std::stoi(this->brickType.hitPoints);
			this->breakScore = std::stoi(this->brickType.breakScore);
		}

		// Load sounds i guess
	}

	return true;
}

void Brick::update(float deltaTime){}

void Brick::render(SDL_Renderer * renderer)
{
	if (this->texture == NULL && this->interactable)
	{
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	}

	SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);
}

bool Brick::isInteractable() const
{
	return this->interactable;
}

void Brick::setInteractable(bool value)
{
	this->interactable = value;
}

void Brick::setBrickType(BrickType type)
{
	this->brickType = type;
}

int Brick::handleHit()
{
	int hitResult = -1;

	// If brick is not immortal
	if (this->hitpoints != -1)
	{
		// Reduce hitpoints
		this->hitpoints--;

		// Set returning value to defined break score value
		hitResult = this->breakScore;

		// play sound

		if (this->hitpoints == 0)
		{
			this->removeTexture();
			this->interactable = false;
		}
		else
		{
			std::string damagedBrickFilename = DAMAGED_BRICK_PREFIX;
			damagedBrickFilename.append(this->brickType.id).append(DAMAGED_BRICK_SUFFIX);
			if (!Util::loadPng(damagedBrickFilename.c_str(), this->surface))
			{
				Util::showMessageBox("Loading .png failed");
				return false;
			}
			else
			{
				// Remove old texture so we can apply damaged texture
				this->texture = nullptr;
			}
		}
	}

	return hitResult;
}

void Brick::removeTexture()
{
	SDL_DestroyTexture(this->texture);
	this->texture = nullptr;
}