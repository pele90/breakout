#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "Scene.h"
#include "Level.h"

#define SCORE_LABEL_NAME "score_value_label"
#define LEVEL_LABEL_NAME "level_value_label"
#define LIVES_LABEL_NAME "heart_"
#define LEVEL_PREFIX "Level_"

class PlayScene : public Scene
{
public:
	PlayScene();
	virtual ~PlayScene();

	virtual bool initialize();
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);
	virtual void destroy();

	void checkUI();
	void updateLives();

private:
	Level* level;
};

#endif // !PLAY_SCENE_H
