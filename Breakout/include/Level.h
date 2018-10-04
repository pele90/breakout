#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

struct LevelDefinition
{
	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string backgroundTexture;
};

struct BrickType
{
	char id;
	std::string texture;
	int hitPoints;
	std::string hitSound;
	std::string breakSound;
	int breakScore;
};

class Level
{
public:
	Level();
	~Level();

	bool initialize();
	void update();
	bool loadLevel(std::string filename);
	void destroy();

private:
	LevelDefinition levelDefinition;
	std::vector<BrickType> brickTypes;
	std::vector< std::vector<char> > bricks;
};

#endif // !LEVEL_H
