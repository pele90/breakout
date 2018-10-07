#include "Scene.h"

Scene::Scene(){}

Scene::~Scene()
{
	SDL_FreeSurface(this->backgroundSurface);
	this->backgroundSurface = NULL;

	SDL_DestroyTexture(this->backgroundTexture);
	this->backgroundTexture = NULL;
}

void Scene::setBackground(std::string filename)
{
	if (!Util::loadPng(filename.c_str(), this->backgroundSurface))
	{
		// LOG error
	}
}

void Scene::renderBackground(SDL_Renderer* renderer)
{
	if (this->backgroundTexture == NULL)
	{
		this->backgroundTexture = SDL_CreateTextureFromSurface(renderer, this->backgroundSurface);
	}

	SDL_RenderCopy(renderer, this->backgroundTexture, nullptr, NULL);
}
