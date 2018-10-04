#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"

#include "UI.h"

class Scene
{
public:
	Scene();
	~Scene();

	virtual bool initialize() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void destroy() = 0;
};

#endif // !SCENE_H
