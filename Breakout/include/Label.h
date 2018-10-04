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
	Label(const char* text);
	Label(const char* text, SDL_Rect transform);
	Label(const char* text, SDL_Rect transform, const char* fontName);
	Label(const char* text, SDL_Rect transform, const char* fontName, int fontSize);
	Label(const char* text, SDL_Rect transform, const char* fontName, int fontSize, SDL_Color fontColor);
	~Label();

	bool initialize();
	virtual void update();
	virtual void render(SDL_Renderer* renderer);
	void destroy();

	void setText(const char* text);
	void setFontName(const char* fontName);
	void setFontColor(SDL_Color color);
	void setFontSize(int size);

private:
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	const char* text;
	const char* fontName;
	SDL_Color fontColor;
	int fontSize;
};

#endif // !LABEL_H
