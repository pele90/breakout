#ifndef END_GAME_SCENE_H
#define END_GAME_SCENE_H

#include "Scene.h"

class EndGameScene : public Scene
{
public:
	EndGameScene();
	virtual ~EndGameScene();

	virtual bool initialize();
};

#endif // !END_GAME_SCENE_H
