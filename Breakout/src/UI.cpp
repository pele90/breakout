#include "UI.h"

UI::UI(){}

UI::~UI(){}

bool UI::initialize(const char* layout)
{
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		return false;
	}

	dataset = new Dataset();
	dataset->parseLayout(layout);

	for (auto it : dataset->getImages())
	{
		it.second->initialize();
	}

	for (auto it : dataset->getButtons())
	{
		it.second->initialize();
	}

	for (auto it : dataset->getLabels())
	{
		it.second->initialize();
	}

	return true;
}

void UI::update(float deltaTime)
{
	std::stringstream fpsText;
	fpsText << (int)deltaTime;

	for (auto it : dataset->getImages())
	{
		it.second->update();
	}

	for (auto it : dataset->getButtons())
	{
		it.second->update();
	}

	for (auto it : dataset->getLabels())
	{
		it.second->update();
	}
}

void UI::render(SDL_Renderer* renderer)
{
	for (auto it : dataset->getImages())
	{
		it.second->render(renderer);
	}

	for (auto it : dataset->getButtons())
	{
		it.second->render(renderer);
	}

	for (auto it : dataset->getLabels())
	{
		it.second->render(renderer);
	}
}

void UI::destroy()
{
	dataset->destroy();
	dataset = NULL;

	TTF_Quit();
}

void UI::setButtonCallback(std::string buttonName, void(*fptr)())
{
	std::map<std::string, Button*> buttons = this->dataset->getButtons();
	std::map<std::string, Button*>::iterator it = buttons.find(buttonName);

	(*it).second->setClickCallback(fptr);
}