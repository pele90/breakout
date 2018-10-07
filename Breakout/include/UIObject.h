#ifndef UI_OBJECT_H
#define UI_OBJECT_H

#include <iostream>
#include <string>

#include "SDL.h"

#include "Resources.h"
#include "Util.h"
#include "Input.h"
#include "GlobalState.h"

class UIObject
{
public:
	UIObject();
	UIObject(SDL_Rect rect);
	virtual ~UIObject();

	virtual void update() = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void destroy() = 0;
	void setTransform(SDL_Rect rect);
	void setName(std::string name);
	std::string getName() const;
	bool isVisible() const;
	void setVisibility(bool value);

protected:
	SDL_Rect transform;
	std::string name;
	bool dirty; // flag to mark when some property is changed so that the new texture with chaned properties can be created
	bool visible = true;
};

#endif // !UI_OBJECT_H
