#include "Button.h"

Button::Button(){}

Button::Button(const char* filename) : textureFilename(filename){}

Button::Button(const char* filename, SDL_Rect transform) : UIObject(transform), textureFilename(filename){}

Button::~Button()
{
}

bool Button::initialize()
{
	// LOAD PNG FROM FILE TO SURFACE
	std::string filename = DEFAULT_TEXTURE_PATH;
	filename.append(this->textureFilename).append(".png");
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == NULL)
	{
		// LOG ERROR
		return false;
	}
	else
	{
		//Convert surface to screen format
		this->surface = SDL_ConvertSurfaceFormat(tempSurface, SDL_PIXELFORMAT_RGBA32 , NULL);
		if (this->surface == NULL)
		{
			std::cout << "Unable to optimize image %s! SDL Error: " << filename.c_str() << SDL_GetError() << std::endl;
			return false;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(tempSurface);
	}

	return true;
}

void Button::update()
{
	if (this->child != NULL)
	{
		this->child->update();
	}
}

void Button::render(SDL_Renderer* renderer)
{
	this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);

	if (this->child != NULL)
	{
		this->child->render(renderer);
	}
}

void Button::destroy()
{
	SDL_DestroyTexture(this->texture);
	this->texture = NULL;

	SDL_FreeSurface(this->surface);
	this->surface = NULL;
}

void Button::setTextureFilename(const char* filename)
{
	this->textureFilename = filename;
}