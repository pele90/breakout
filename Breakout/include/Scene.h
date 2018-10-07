#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"

#include "UI.h"
#include "Util.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual bool initialize() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void destroy() = 0;

	void setBackground(std::string filename);
	void renderBackground(SDL_Renderer* renderer);

protected:
	SDL_Surface* backgroundSurface;
	SDL_Texture* backgroundTexture;
	UI* ui;
};

#endif // !SCENE_H
