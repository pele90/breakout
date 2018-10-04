#ifndef UI_OBJECT_H
#define UI_OBJECT_H

#include <iostream>

#include "SDL.h"

#include "Resources.h"

class UIObject
{
public:
	UIObject();
	UIObject(SDL_Rect rect);
	virtual ~UIObject();

	virtual void update() = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	void addChild(UIObject* child);
	void setTransform(SDL_Rect rect);

protected:
	SDL_Rect transform;
	UIObject* child = NULL;
};

#endif // !UI_OBJECT_H
