#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>

#include "tinyxml2.h"

#include "Resources.h"
#include "Brick.h"

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

	bool initialize();
	void update(float deltaTime);
	bool loadLevel(std::string filename);
	bool createLevel();
	bool checkXmlResult(tinyxml2::XMLError error);
	void render(SDL_Renderer* renderer);
	void destroy();

private:
	void extractBricks(const char* text);

private:
	LevelDefinition* levelDefinition;
	std::map<std::string, BrickType*> brickTypes;
	std::vector< std::vector<std::string> > bricks;
	std::vector<Brick*> bricksObjects;
};

#endif // !LEVEL_H
