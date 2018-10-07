#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "Scene.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

	virtual bool initialize();
};

#endif // !MAIN_MENU_SCENE_H
