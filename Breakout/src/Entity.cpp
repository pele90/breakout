#include "Entity.h"

Entity::Entity(){}

Entity::Entity(std::string filename) : textureFilename(filename){}

Entity::~Entity(){}

void Entity::render(SDL_Renderer * renderer)
{
	if (this->texture == NULL)
	{
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	}

	SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);
}

void Entity::destroy()
{
	SDL_DestroyTexture(this->texture);
	this->texture = NULL;

	SDL_FreeSurface(this->surface);
	this->surface = NULL;
}

void Entity::setTransform(SDL_Rect rect)
{
	this->transform = rect;
}

void Entity::setTextureFilename(std::string filename)
{
	this->textureFilename = filename;
}

std::string Entity::getTextureFilename() const
{
	return this->textureFilename;
}

SDL_Rect Entity::getTransform() const
{
	return this->transform;
}