#ifndef BUTTON_H
#define BUTTON_H

#include "UIObject.h"
#include "SDL_image.h"

#define HOVERED_ALPHA 200
#define FULL_ALPHA 255

class Button : public UIObject
{
public:
	Button();
	Button(const char* filename);
	Button(const char* filename, SDL_Rect transform);
	virtual ~Button();

	bool initialize();
	virtual void update();
	virtual void render(SDL_Renderer* renderer);
	void destroy();

	void setTextureFilename(const char* filename);
	bool mouseHover();
	void setClickCallback(void(*fptr)());

private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	std::string textureFilename;
	bool hover;
	void(*onClick)(); // returns void, called onClick, no arguments
};

#endif // !BUTTON_H
