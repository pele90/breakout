#include "ImageObject.h"

ImageObject::ImageObject() {}

ImageObject::ImageObject(const char* filename) : textureFilename(filename) {}

ImageObject::ImageObject(const char* filename, SDL_Rect transform) : UIObject(transform), textureFilename(filename) {}

ImageObject::~ImageObject(){}

bool ImageObject::initialize()
{
	if (!Util::loadPng(this->textureFilename.c_str(), this->surface))
	{
		// LOG error
	}
	else
	{
		dirty = true;
	}

	return true;
}

void ImageObject::update()
{
}

void ImageObject::render(SDL_Renderer* renderer)
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

void ImageObject::destroy()
{
	SDL_DestroyTexture(this->texture);
	this->texture = NULL;

	SDL_FreeSurface(this->surface);
	this->surface = NULL;
}

void ImageObject::setTextureFilename(const char* filename)
{
	this->textureFilename = filename;
}

void ImageObject::removeTexture()
{
	SDL_DestroyTexture(this->texture);
	this->texture = NULL;
}