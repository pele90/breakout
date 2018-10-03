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
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == nullptr)
			{
				std::cout << "Failed to create renderer : " << SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				// Set size of renderer to the same as window
				SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

				// Set color of renderer to red
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}

			gameGUI = new GameGUI();
			gameGUI->initialize(renderer);

			//Get window surface 
			//screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white 
			//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

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
	gameGUI->update(renderer, deltaTime);
}

void Game::render()
{
	gameGUI->render(renderer);

	// Render the changes above
	SDL_RenderPresent(renderer);
}

void Game::destroy()
{
	//Deallocate surface 
	SDL_FreeSurface(screenSurface); 
	screenSurface = NULL;
	
	//Destroy window 
	SDL_DestroyWindow(window); 
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	gameGUI->destroy();
	gameGUI = NULL;
	
	//Quit SDL subsystems 
	SDL_Quit();
}