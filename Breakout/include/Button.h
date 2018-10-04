#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "UIObject.h"



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

private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	std::string textureFilename;
};

#endif // !BUTTON_H
