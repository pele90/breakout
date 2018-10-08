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
		Util::showMessageBox("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
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
			Util::showMessageBox("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
			return false;
		}
		else
		{
			this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

			if (this->renderer == nullptr)
			{
				Util::showMessageBox("Failed to create renderer : " + std::string(SDL_GetError()));
				return false;
			}
			else
			{
				// Set color of renderer to white
				SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);

				// SOUND MANAGER
				SoundManager::initialize();

				// SCENE MANAGER
				sceneManager = new SceneManager();
				sceneManager->initialize();

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					Util::showMessageBox("SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()));
					return false;
				}
			}
		}
	}
	return true;
}

void Game::run()
{
	float frame = 0;
	unsigned int lastFrameTime = 0;
	float timeDifference, deltaTime;
	unsigned int capTimer = 0;

	if (!this->initialize())
	{
		return;
	}
	else
	{
		while (GlobalState::getCurrentState() != GlobalState::GameState::Exit)
		{
			capTimer = SDL_GetTicks();
			timeDifference = SDL_GetTicks() - lastFrameTime;
			lastFrameTime += timeDifference;
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
	// If Input returns false, then the user pressed exit button
	if (!Input::handleInputs())
	{
		GlobalState::setCurrentState(GlobalState::GameState::Exit);
	}
	else
	{
		this->sceneManager->update(deltaTime);
	}	
}

void Game::render()
{
	SDL_RenderClear(this->renderer);

	this->sceneManager->render(this->renderer);

	SDL_RenderPresent(this->renderer);
}

void Game::destroy()
{
	this->sceneManager->destroy();
	delete this->sceneManager;
	this->sceneManager = NULL;

	SoundManager::destroy();

	SDL_DestroyWindow(this->window);
	this->window = NULL;

	SDL_DestroyRenderer(this->renderer);
	this->renderer = NULL;

	//Quit SDL subsystems 
	SDL_Quit();
}