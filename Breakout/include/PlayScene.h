#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "Scene.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	virtual bool initialize();
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);
	virtual void destroy();

private:
	UI* ui;
};

#endif // !PLAY_SCENE_H
