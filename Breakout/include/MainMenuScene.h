#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "Scene.h"
#include "Level.h"
#include "Brick.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	~MainMenuScene();

	virtual bool initialize();
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);
	virtual void destroy();

private:
	Level* level;
	UI* ui;
};

#endif // !MAIN_MENU_SCENE_H
