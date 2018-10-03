#ifndef GAME_GUI_H
#define GAME_GUI_H

#include "SDL_ttf.h"

class GameGUI 
{
public:
	GameGUI();
	~GameGUI();
	bool initialize();
	void destroy();

private:
	TTF_Font *m_font;
	SDL_Color m_fontColor = { 0, 0, 0 };

};

#endif // !GAME_GUI_H
