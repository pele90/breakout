#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "tinyxml2.h"

#include "Ball.h"
#include "Brick.h"
#include "Player.h"
#include "Resources.h"

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
	void render(SDL_Renderer* renderer);
	void destroy();

	bool isUiChanged() const;
	void setUiChanged(bool value);
	void ballFollowPlayer();

private:
	bool initLevel(std::string filename);
	bool createLevel(LevelDefinition levelDefinition);
	bool checkXmlResult(tinyxml2::XMLError error);
	void extractBricks(LevelDefinition levelDefinition, const char* text);

	void handleBallFieldInteractions();
	void checkBallBrickCollision(Ball* ball, Brick* brick, float deltaTime);
	void ballBrickResponse(Brick::BrickCollisionResponse, Ball* ball, float deltaTime);

	void checkBallPaddleCollision(float deltaTime);
	float getCollisionReflection(float hitx);
	void setDirection(Ball* ball, float newdirx, float newdiry, float deltaTime);

	bool winCondition();

private:
	Ball* ball;
	Player* player;
	std::vector<Brick*> bricksObjects;
	std::map<std::string, BrickType*> brickTypes;
	std::vector< std::vector<std::string> > bricks;
	bool uiChanged;
	bool isBallFollowingPlayer;
	int numOfDestroyableBricks; // number of times ball has to hit bricks to finish level 
};

#endif // !LEVEL_H
