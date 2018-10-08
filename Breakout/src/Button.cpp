#include "Button.h"

Button::Button() : surface(nullptr){}

Button::Button(const char* filename) : textureFilename(filename){}

Button::Button(const char* filename, SDL_Rect transform) : UIObject(transform), textureFilename(filename){}

Button::~Button(){}

bool Button::initialize()
{
	if (!Util::loadPng(this->textureFilename.c_str(), this->surface))
	{
		Util::showMessageBox("Loading .png failed");
		return false;
	}
	else
	{
		dirty = true;
		this->onClick = nullptr;
	}

	return true;
}

void Button::update()
{
	if (this->mouseHover())
	{
		if (!this->hover)
		{
			this->dirty = true;

			SDL_SetSurfaceAlphaMod(this->surface, HOVERED_BUTTON_ALPHA);

			int x = this->transform.x - HOVER_BUTTON_POSITION_VALUE;
			int y = this->transform.y - HOVER_BUTTON_POSITION_VALUE;
			int w = this->transform.w + HOVER_BUTTON_SCALE_VALUE;
			int h = this->transform.h + HOVER_BUTTON_SCALE_VALUE;

			SDL_Rect newRect = { x, y, w, h };

			this->transform = newRect;

			this->hover = true;
		}

		if (Input::isLeftMouseButtonUp())
		{
			if (this->onClick != NULL)
			{
				SoundManager::playSFX(BUTTON_CLICK_SOUND);
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
			
			int x = this->transform.x + HOVER_BUTTON_POSITION_VALUE;
			int y = this->transform.y + HOVER_BUTTON_POSITION_VALUE;
			int w = this->transform.w - HOVER_BUTTON_SCALE_VALUE;
			int h = this->transform.h - HOVER_BUTTON_SCALE_VALUE;

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
		if (this->texture != nullptr)
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
	this->surface = nullptr;

	SDL_DestroyTexture(this->texture);
	this->texture = nullptr;

	this->onClick = nullptr;
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