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
	if (!dataset->parseLayout(layout))
	{
		return false;
	}

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
		if (it.second->isVisible())
		{
			it.second->render(renderer);
		}
	}

	for (auto it : dataset->getButtons())
	{
		if (it.second->isVisible())
		{
			it.second->render(renderer);
		}
	}

	for (auto it : dataset->getLabels())
	{
		if (it.second->isVisible())
		{
			it.second->render(renderer);
		}
	}
}

void UI::destroy()
{
	dataset->destroy();
	delete dataset;
	dataset = NULL;

	TTF_Quit();
}

void UI::changeLabelVisibility(std::string labelName, bool value)
{
	std::map<std::string, Label*> labels = this->dataset->getLabels();
	std::map<std::string, Label*>::iterator it = labels.find(labelName);
	(*it).second->setVisibility(value);
}

void UI::changeImageVisibility(std::string imageName, bool value)
{
	std::map<std::string, ImageObject*> images = this->dataset->getImages();
	std::map<std::string, ImageObject*>::iterator it = images.find(imageName);
	(*it).second->setVisibility(value);
}

void UI::setButtonCallback(std::string buttonName, void(*fptr)())
{
	std::map<std::string, Button*> buttons = this->dataset->getButtons();
	std::map<std::string, Button*>::iterator it = buttons.find(buttonName);
	(*it).second->setClickCallback(fptr);
}

void UI::changeLabelText(std::string labelName, std::string text)
{
	std::map<std::string, Label*> labels = this->dataset->getLabels();
	std::map<std::string, Label*>::iterator it = labels.find(labelName);
	(*it).second->setText(text);
}

void UI::hideImage(std::string imageName)
{
	std::map<std::string, ImageObject*> images = this->dataset->getImages();
	std::map<std::string, ImageObject*>::iterator it = images.find(imageName);
	(*it).second->removeTexture();
}