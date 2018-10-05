#include "Label.h"

#define DEFAULT_LABEL_WIDTH 100
#define DEFAULT_LABEL_HEIGHT 50

constexpr SDL_Color default_font_color = { 0, 0, 0, 0 };

Label::Label() {}

Label::Label(std::string text)
{
	this->text = text;
	this->transform = { 0, 0, DEFAULT_LABEL_WIDTH, DEFAULT_LABEL_HEIGHT };
	this->fontName = DEFAULT_FONT_NAME;
	this->fontSize = DEFAULT_FONT_SIZE;
	this->fontColor = default_font_color;
}

Label::Label(std::string text, SDL_Rect transform) : UIObject(transform)
{
	this->text = text;
	this->fontName = DEFAULT_FONT_NAME;
	this->fontSize = DEFAULT_FONT_SIZE;
	this->fontColor = default_font_color;
}

Label::Label(std::string text, SDL_Rect transform, std::string fontName) : UIObject(transform)
{
	this->text = text;
	this->fontName = fontName;
	this->fontSize = DEFAULT_FONT_SIZE;
	this->fontColor = default_font_color;
}

Label::Label(std::string text, SDL_Rect transform, std::string fontName, int fontSize) : UIObject(transform)
{
	this->text = text;
	this->fontName = fontName;
	this->fontSize = fontSize;
	this->fontColor = default_font_color;
}

Label::Label(std::string text, SDL_Rect transform, std::string fontName, int fontSize, SDL_Color fontColor) : UIObject(transform)
{
	this->text = text;
	this->fontName = fontName;
	this->fontSize = fontSize;
	this->fontColor = fontColor;
}

Label::~Label() {}

bool Label::initialize()
{
	std::string fontFilename = DEFAULT_FONT_PATH;
	fontFilename.append(this->fontName).append(".ttf");
	this->font = TTF_OpenFont(fontFilename.c_str(), this->fontSize);
	if (this->font == NULL)
	{
		return false;
	}

	this->dirty = true;

	return true;
}

void Label::update()
{
}

void Label::render(SDL_Renderer* renderer)
{
	if (this->dirty)
	{
		if (this->texture != NULL)
		{
			SDL_DestroyTexture(this->texture);
		}

		if (this->surface != NULL)
		{
			SDL_FreeSurface(this->surface);
		}

		this->surface = TTF_RenderText_Blended(this->font, this->text.c_str(), this->fontColor);
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
		SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);

		this->dirty = false;
	}
	else
	{
		SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);
	}
}

void Label::destroy()
{
	TTF_CloseFont(this->font);
	this->font = NULL;

	SDL_DestroyTexture(this->texture);
	this->texture = NULL;

	SDL_FreeSurface(this->surface);
	this->surface = NULL;
}

void Label::setText(std::string text)
{
	this->text = text;
}

void Label::setFontName(std::string fontName)
{
	this->fontName = fontName;
}

void Label::setFontColor(SDL_Color color)
{
	this->fontColor = color;
}

void Label::setFontSize(int size)
{
	this->fontSize = size;
}