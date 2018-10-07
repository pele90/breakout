#include "Button.h"

Button::Button() : surface(NULL){}

Button::Button(const char* filename) : textureFilename(filename){}

Button::Button(const char* filename, SDL_Rect transform) : UIObject(transform), textureFilename(filename){}

Button::~Button(){}

bool Button::initialize()
{
	if (!Util::loadPng(this->textureFilename.c_str(), this->surface))
	{
		// LOG error
	}
	else
	{
		this->onClick = NULL;

		dirty = true;
	}

	return true;
}

void Button::update()
{
	if (mouseHover())
	{
		if (!this->hover)
		{
			this->dirty = true;

			SDL_SetSurfaceAlphaMod(this->surface, HOVERED_ALPHA);

			int x = this->transform.x - 3;
			int y = this->transform.y - 3;
			int w = this->transform.w + 6;
			int h = this->transform.h + 6;

			SDL_Rect newRect = { x, y, w, h };

			this->transform = newRect;

			this->hover = true;
		}

		if (Input::isLeftMouseButtonUp())
		{
			if (this->onClick != NULL)
			{
				onClick();	
			}
		}
	}
	else
	{
		if (this->hover)
		{
			this->dirty = true;

			SDL_SetSurfaceAlphaMod(this->surface, FULL_ALPHA);
			
			int x = this->transform.x + 3;
			int y = this->transform.y + 3;
			int w = this->transform.w - 6;
			int h = this->transform.h - 6;

			SDL_Rect newRect = { x, y, w, h };

			this->transform = newRect;

			this->hover = false;
		}
	}
}

void Button::render(SDL_Renderer* renderer)
{
	if (this->dirty)
	{
		if (this->texture != NULL)
		{
			SDL_DestroyTexture(this->texture);
		}

		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
		SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);

		this->dirty = false;
	}
	else
	{
		SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);
	}
}

void Button::destroy()
{
	SDL_FreeSurface(this->surface);
	this->surface = NULL;

	SDL_DestroyTexture(this->texture);
	this->texture = NULL;

	this->onClick = NULL;
}

void Button::setTextureFilename(const char* filename)
{
	this->textureFilename = filename;
}

bool Button::mouseHover()
{
	int x, y;
	Input::getInstance().getMouse(x, y);
	SDL_Point point = { x, y };

	return SDL_PointInRect(&point, &this->transform);
}

void Button::setClickCallback(void(*fptr)())
{
	this->onClick = fptr;
}