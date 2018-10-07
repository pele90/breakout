#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "Scene.h"
#include "Level.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	virtual ~PlayScene();

	virtual bool initialize();
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);
	virtual void destroy();

private:
	Level* level;
};

#endif // !PLAY_SCENE_H
