#include "Game.h"

Game::Game() : window(NULL) {}

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
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0, &dm);
		GlobalState::setScreenWidth(DEFAULT_SCREEN_WIDTH);
		GlobalState::setScreenHeight(DEFAULT_SCREEN_HEIGHT);

		//Create window 
		this->window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (this->window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			SDL_SetWindowBordered(window, SDL_TRUE);

			this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
			//SDL_RenderSetLogicalSize(renderer, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

			if (this->renderer == nullptr)
			{
				std::cout << "Failed to create renderer : " << SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				// Set size of renderer to the same as window
				//SDL_RenderSetLogicalSize(this->renderer, GlobalState::getScreenWidth(), GlobalState::getScreenHeight());

				// Set color of renderer to white
				SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);

				sceneManager = new SceneManager();
				sceneManager->initialize();

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
				}
			}
		}
	}
	return true;
}

void Game::run()
{
	this->isRunning = true;
	float frame = 0;
	unsigned int lastTime = 0;
	float timeDifference, deltaTime;
	unsigned int capTimer = 0;
	int loops;

	if (!this->initialize())
	{
		return;
	}
	else
	{
		while (isRunning)
		{
			capTimer = SDL_GetTicks();
			timeDifference = SDL_GetTicks() - lastTime;
			lastTime += timeDifference;
			deltaTime = (frame / (SDL_GetTicks() / 1000.f)) * 0.001;

			this->update(timeDifference * 0.001);

			this->render();

			frame++;

			//If frame finished early 
			if ((SDL_GetTicks() - capTimer) < screen_ticks_per_frame)
			{
				//Wait remaining time 
				SDL_Delay(screen_ticks_per_frame - (SDL_GetTicks() - capTimer));
			}
		}
	}
}

void Game::update(float deltaTime)
{
	this->isRunning = Input::handleInputs();

	this->sceneManager->update(deltaTime);
}

void Game::render()
{
	SDL_RenderClear(this->renderer);

	this->sceneManager->render(this->renderer);

	// Render the changes above
	SDL_RenderPresent(this->renderer);
}

void Game::destroy()
{
	this->sceneManager->destroy();
	delete this->sceneManager;
	this->sceneManager = NULL;

	//Destroy window 
	SDL_DestroyWindow(this->window);
	this->window = NULL;

	SDL_DestroyRenderer(this->renderer);
	this->renderer = NULL;

	//Quit SDL subsystems 
	SDL_Quit();
}