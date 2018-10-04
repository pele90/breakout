#include "UI.h"

UI::UI()
{
}

UI::~UI(){}

bool UI::initialize()
{
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		return false;
	}

	dataset = new Dataset();
	dataset->parseLayout("main_menu");

	for (auto it : dataset->getButtons())
	{
		it->initialize();
	}

	for (auto it : dataset->getLabels())
	{
		it->initialize();
	}

	return true;
}

void UI::update(float deltaTime)
{
	std::stringstream fpsText;
	fpsText << (int)deltaTime;

	for (auto it : dataset->getButtons())
	{
		it->update();
	}

	for (auto it : dataset->getLabels())
	{
		it->update();
	}
}

void UI::render(SDL_Renderer* renderer)
{
	for (auto it : dataset->getButtons())
	{
		it->render(renderer);
	}

	for (auto it : dataset->getLabels())
	{
		it->render(renderer);
	}
}

void UI::destroy()
{
	TTF_Quit();
}