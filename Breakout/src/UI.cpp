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

	Dataset* dataset = new Dataset();
	dataset->parseLayout("main_menu");

	SDL_Rect labelRect = { 100, 100, 200, 100 };
	this->label = Label("Hello world", labelRect);
	if (!label.initialize())
	{
		return false;
	}

	SDL_Rect playRect = { 175, 150, 50, 50 };
	this->button = Button("playButton", playRect);
	if (!button.initialize())
	{
		return false;
	}
	this->button.addChild((UIObject*)&label);

	return true;
}

void UI::update(float deltaTime)
{
	std::stringstream fpsText;
	fpsText << (int)deltaTime;

	//this->label.update();
	this->button.update();
}

void UI::render(SDL_Renderer* renderer)
{
	//this->label.render(renderer);
	this->button.render(renderer);
}

void UI::destroy()
{
	TTF_Quit();
}