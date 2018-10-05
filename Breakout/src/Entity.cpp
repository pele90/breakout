#include "Entity.h"

Entity::Entity(){}

Entity::Entity(std::string filename) : textureFilename(filename){}

Entity::~Entity(){}

void Entity::setTransform(SDL_Rect rect)
{
	this->transform = rect;
}

void Entity::setTextureFilename(std::string filename)
{
	this->textureFilename = filename;
}

SDL_Rect Entity::getTransform() const
{
	return this->transform;
}

std::string Entity::getTextureFilename() const
{
	return this->textureFilename;
}