#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "Input.h"


class Entity
{
public:
	Entity();
	Entity(std::string filename);
	virtual ~Entity();

	virtual bool initialize() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void destroy() = 0;

	void setTransform(SDL_Rect rect);
	void setTextureFilename(std::string filename);
	SDL_Rect getTransform() const;
	std::string getTextureFilename() const;

protected:
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect transform;
	std::string textureFilename;
};

#endif // !ENTITY_H
