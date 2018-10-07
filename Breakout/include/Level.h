#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>

#include "tinyxml2.h"

#include "Resources.h"
#include "Brick.h"
#include "Ball.h"
#include "Player.h"

struct LevelDefinition
{
	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string backgroundTexture;
};

class Level
{
public:
	Level();
	~Level();

	bool initialize(std::string level);
	void update(float deltaTime);
	bool loadLevel(std::string filename);
	bool createLevel();
	bool checkXmlResult(tinyxml2::XMLError error);
	void render(SDL_Renderer* renderer);
	void destroy();

public:
	bool winCondition();
	bool isUiChanged() const;
	void setUiChanged(bool value);
	void ballFollowPlayer();

private:
	void extractBricks(const char* text);
	void checkBrickCollision(Ball* ball, Brick* brick, float deltaTime);
	void checkPaddleCollision(float deltaTime);
	bool paddleCollision(Ball* ball);
	float getReflection(float hitx);
	void setDirection(Ball* ball, float newdirx, float newdiry, float deltaTime);
	void ballBrickResponse(Brick::BrickResponse, Ball* ball, float deltaTime);

private:
	LevelDefinition levelDefinition;
	std::map<std::string, BrickType*> brickTypes;
	std::vector< std::vector<std::string> > bricks;
	int numOfDestroyableBricks;
	std::vector<Brick*> bricksObjects;
	std::vector<Ball*> balls;
	bool isBallFollowingPlayer;
	Player* player;
	bool uiChanged;
};

#endif // !LEVEL_H
