#ifndef UI_H
#define UI_H

#include <sstream>
#include <map>

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
	bool initialize(const char* layout);
	void update(float deltaTime);
	void render(SDL_Renderer* renderer);
	void destroy();
	void setButtonCallback(std::string buttonName, void(*fptr)());
	void changeLabelText(std::string labelName, std::string text);
	void hideImage(std::string imageName);

private:
	Dataset* dataset;
};

#endif // !UI_H
