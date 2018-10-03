#include "GameGUI.h"

GameGUI::GameGUI()
{
}

GameGUI::~GameGUI(){}

bool GameGUI::initialize(SDL_Renderer *renderer)
{
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		return false;
	}

	m_font = TTF_OpenFont("assets/font/Lato-Regular.ttf", 28);
	if (m_font == NULL)
	{
		return false;
	}

	m_fontFpsSurface = TTF_RenderText_Solid(m_font, "Ovo je testni primjerak", m_fontColor);
	m_fontFpsTexture = SDL_CreateTextureFromSurface(renderer, m_fontFpsSurface);

	return true;
}

void GameGUI::update(SDL_Renderer *renderer, float deltaTime)
{
	std::stringstream fpsText;
	fpsText << (int)deltaTime;

	m_fontFpsSurface = TTF_RenderText_Solid(m_font, fpsText.str().c_str(), m_fontColor);
	m_fontFpsTexture = SDL_CreateTextureFromSurface(renderer, m_fontFpsSurface);
}

void GameGUI::render(SDL_Renderer *renderer)
{
	// Clear the window and make it all red
	SDL_RenderClear(renderer);


	SDL_Rect solidRect = { 50, 0, 100, 50 };

	// Render our text objects ( like normal )
	SDL_RenderCopy(renderer, m_fontFpsTexture, nullptr, &solidRect);
}

void GameGUI::destroy()
{
	TTF_CloseFont(m_font);
	m_font = NULL;
	TTF_Quit();
}