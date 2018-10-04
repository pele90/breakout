#include "Game.h"

Game::Game() : window(NULL){}

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
		this->window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (this->window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

			if (this->renderer == nullptr)
			{
				std::cout << "Failed to create renderer : " << SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				// Set size of renderer to the same as window
				SDL_RenderSetLogicalSize(this->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

				// Set color of renderer to white
				SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
				}
			}

			this->ui = new UI();
			this->ui->initialize();
		}
	}
	return true;
}

void Game::run()
{
	this->isRunning = true;
	int frame = 0;
	unsigned int lastTime = 0;
	float deltaTime;
	unsigned int capTimer = 0;

	if (!this->initialize())
	{
		return;
	}
	else
	{
		while (isRunning)
		{
			capTimer = SDL_GetTicks();
			deltaTime = SDL_GetTicks() - lastTime;
			lastTime += deltaTime;

			this->update(frame / (SDL_GetTicks() / 1000.f));

			this->render();

			frame++;

			//If frame finished early 
			if((SDL_GetTicks() - capTimer) < SCREEN_TICKS_PER_FRAME )
			{ 
				//Wait remaining time 
				SDL_Delay( SCREEN_TICKS_PER_FRAME - (SDL_GetTicks() - capTimer));
			}
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
	this->ui->update(deltaTime);
}

void Game::render()
{
	SDL_RenderClear(renderer);

	this->ui->render(this->renderer);

	// Render the changes above
	SDL_RenderPresent(this->renderer);
}

void Game::destroy()
{
	//Destroy window 
	SDL_DestroyWindow(this->window);
	this->window = NULL;

	SDL_DestroyRenderer(this->renderer);
	this->renderer = NULL;

	this->ui->destroy();
	this->ui = NULL;
	
	//Quit SDL subsystems 
	SDL_Quit();
}