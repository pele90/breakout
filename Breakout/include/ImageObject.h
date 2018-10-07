#ifndef IMAGE_OBJECT_H
#define IMAGE_OBJECT_H

#include "UIObject.h"
#include "SDL_image.h"

class ImageObject : public UIObject
{
public:
	ImageObject();
	ImageObject(const char* filename);
	ImageObject(const char* filename, SDL_Rect transform);
	virtual ~ImageObject();

	bool initialize();
	virtual void update();
	virtual void render(SDL_Renderer* renderer);
	void destroy();

	void setTextureFilename(const char* filename);
	void removeTexture();

private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	std::string textureFilename;
};

#endif // !IMAGE_OBJECT_H