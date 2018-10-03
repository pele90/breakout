#include "Game.h"

Game::Game() : window(NULL), screenSurface(NULL){}

Game::~Game()
{
	this->destroy();
}

bool Game::initialize()
{
	//Initialize SDL 
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else 
	{
		//Create window 
		window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			//Get window surface 
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white 
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			////Update the surface 
			//SDL_UpdateWindowSurface(window);
		}
	}
	return true;
}

void Game::start()
{
	this->isRunning = true;
	int frame = 0;
	unsigned int lastTime = 0;
	float deltaTime;

	if (!this->initialize())
	{
		return;
	}
	else
	{
		while (isRunning)
		{
			deltaTime = SDL_GetTicks() - lastTime;
			lastTime += deltaTime;

			std::cout << frame / (SDL_GetTicks() / 1000.f) << std::endl;

			this->update(deltaTime);

			frame++;
		}
	}
}

void Game::update(float deltaTime)
{
	//Handle events on queue
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			this->isRunning = false;
		}
	}

	// update physics

	// update gui

	// draw


}

void Game::render()
{
}

void Game::destroy()
{
	//Deallocate surface 
	SDL_FreeSurface(screenSurface); 
	screenSurface = NULL;
	
	//Destroy window 
	SDL_DestroyWindow(window); 
	window = NULL;
	
	//Quit SDL subsystems 
	SDL_Quit();
}