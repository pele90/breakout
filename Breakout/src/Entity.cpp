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