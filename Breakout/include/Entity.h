#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "Constants.h"
#include "GlobalState.h"
#include "Input.h"
#include "SoundManager.h"
#include "Util.h"


class Entity
{
public:
	Entity();
	Entity(std::string filename);
	virtual ~Entity();

	virtual bool initialize() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer);
	virtual void destroy();

	std::string getTextureFilename() const;
	SDL_Rect getTransform() const;
	void setTransform(SDL_Rect rect);
	void setTextureFilename(std::string filename);

protected:
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect transform;
	std::string textureFilename;
};

#endif // !ENTITY_H
