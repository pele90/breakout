#ifndef GAME_GUI_H
#define GAME_GUI_H

#include "SDL.h"
#include "SDL_ttf.h"

#include <sstream>

class GameGUI 
{
public:
	GameGUI();
	~GameGUI();
	bool initialize(SDL_Renderer *renderer);
	void update(SDL_Renderer *renderer, float deltaTime);
	void render(SDL_Renderer *renderer);
	void destroy();

private:
	TTF_Font *m_font;
	SDL_Color m_fontColor = { 0, 0, 0 };

	SDL_Surface *m_fontFpsSurface;
	SDL_Texture *m_fontFpsTexture;
	SDL_Rect m_fontFpsPosition;

};

#endif // !GAME_GUI_H
