#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "UIObject.h"

class Label : public UIObject
{
public:
	Label();
	Label(std::string text);
	Label(std::string text, SDL_Rect transform);
	Label(std::string text, SDL_Rect transform, std::string fontName);
	Label(std::string text, SDL_Rect transform, std::string fontName, int fontSize);
	Label(std::string text, SDL_Rect transform, std::string fontName, int fontSize, SDL_Color fontColor);
	virtual ~Label();

	bool initialize();
	virtual void update();
	virtual void render(SDL_Renderer* renderer);
	void destroy();

	void setText(std::string text);
	void setFontName(std::string fontName);
	void setFontColor(SDL_Color color);
	void setFontSize(int size);

private:
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	std::string text;
	std::string fontName;
	SDL_Color fontColor;
	int fontSize;
};

#endif // !LABEL_H
