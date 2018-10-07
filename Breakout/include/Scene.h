#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"

#include "Constants.h"
#include "UI.h"
#include "Util.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual bool initialize() = 0;
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);
	virtual void destroy();

	bool setBackground(std::string filename);
	void renderBackground(SDL_Renderer* renderer);

protected:
	UI* ui;
	SDL_Surface* backgroundSurface;
	SDL_Texture* backgroundTexture;
};

#endif // !SCENE_H
