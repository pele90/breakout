#ifndef UI_H
#define UI_H

#include <map>
#include <sstream>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Button.h"
#include "Dataset.h"
#include "Label.h"


class UI 
{
public:
	UI();
	~UI();
	bool initialize(const char* layout);
	void update(float deltaTime);
	void render(SDL_Renderer* renderer);
	void destroy();

	void changeLabelVisibility(std::string labelName, bool value);
	void setButtonCallback(std::string buttonName, void(*fptr)());
	void changeLabelText(std::string labelName, std::string text);
	void hideImage(std::string imageName);

private:
	Dataset* dataset;
};

#endif // !UI_H
