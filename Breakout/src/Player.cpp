#include "Player.h"

Player::Player() {}

Player::Player(std::string filename) : Entity(filename) {}

Player::~Player() {}

bool Player::initialize()
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
		this->surface = SDL_ConvertSurfaceFormat(tempSurface, SDL_PIXELFORMAT_RGBA32, NULL);
		if (this->surface == NULL)
		{
			std::cout << "Unable to optimize image %s! SDL Error: " << filename.c_str() << SDL_GetError() << std::endl;
			return false;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(tempSurface);

		SDL_Rect rect = { 400, 650, 200, 30 };
		this->setTransform(rect);
	}

	return true;
}

void Player::update(float deltaTime)
{
	if (Input::getInstance().isLeftArrowPressed())
	{
		this->transform.x -= 10;
	}

	if (Input::getInstance().isRightArrowPressed())
	{
		this->transform.x += 10;
	}
}

void Player::render(SDL_Renderer* renderer)
{
	if (this->texture == NULL)
	{
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	}

	SDL_RenderCopy(renderer, this->texture, nullptr, &this->transform);
}

void Player::destroy()
{
}