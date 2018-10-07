#ifndef END_GAME_SCENE_H
#define END_GAME_SCENE_H

#include "Scene.h"

class EndGameScene : public Scene
{
public:
	EndGameScene();
	virtual ~EndGameScene();

	virtual bool initialize();
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);
	virtual void destroy();
};

#endif // !END_GAME_SCENE_H
