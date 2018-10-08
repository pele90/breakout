#include "Scene.h"

Scene::Scene(){}

Scene::~Scene(){}

void Scene::update(float deltaTime)
{
	this->ui->update(deltaTime);
}

void Scene::render(SDL_Renderer * renderer)
{
	this->renderBackground(renderer);

	this->ui->render(renderer);
}

void Scene::destroy()
{
	this->ui->destroy();
	delete ui;
	this->ui = nullptr;

	SDL_FreeSurface(this->backgroundSurface);
	this->backgroundSurface = nullptr;

	SDL_DestroyTexture(this->backgroundTexture);
	this->backgroundTexture = nullptr;
}

void Scene::changeLabelVisibility(std::string labelName, bool value)
{
	this->ui->changeLabelVisibility(labelName, value);
}

bool Scene::setBackground(std::string filename)
{
	if (!Util::loadPng(filename.c_str(), this->backgroundSurface))
	{
		Util::showMessageBox("Setting background failed");
		return false;
	}

	return true;
}

void Scene::renderBackground(SDL_Renderer* renderer)
{
	if (this->backgroundTexture == NULL)
	{
		this->backgroundTexture = SDL_CreateTextureFromSurface(renderer, this->backgroundSurface);
	}

	SDL_RenderCopy(renderer, this->backgroundTexture, nullptr, NULL);
}

