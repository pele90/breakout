#ifndef UI_H
#define UI_H

#include <sstream>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Label.h"
#include "Button.h"
#include "Dataset.h"


class UI 
{
public:
	UI();
	~UI();
	bool initialize();
	void update(float deltaTime);
	void render(SDL_Renderer* renderer);
	void destroy();

private:
	Label label;
	Button button;
	SDL_PixelFormat fmt;
};

#endif // !UI_H
