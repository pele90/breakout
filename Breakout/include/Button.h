#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "UIObject.h"

#define PRESSED_ALPHA 128
#define FULL_ALPHA 255

class Button : public UIObject
{
public:
	Button();
	Button(const char* filename);
	Button(const char* filename, SDL_Rect transform);
	~Button();

	bool initialize();
	virtual void update();
	virtual void render(SDL_Renderer* renderer);
	void destroy();

	void setTextureFilename(const char* filename);
	bool mouseHover();

private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	std::string textureFilename;
	bool hover;
};

#endif // !BUTTON_H
