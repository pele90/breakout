#ifndef UI_OBJECT_H
#define UI_OBJECT_H

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "Constants.h"
#include "GlobalState.h"
#include "Input.h"
#include "Util.h"

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
	std::string name;
	SDL_Rect transform;
	bool dirty; // flag to mark when some property is changed so that the new texture with chaned properties can be created
	bool visible = true;
};

#endif // !UI_OBJECT_H
