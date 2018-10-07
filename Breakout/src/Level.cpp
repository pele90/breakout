#include "Level.h"
#include <sstream>

Level::Level()
{
}

Level::~Level()
{
}

bool Level::initialize()
{
	if (!this->loadLevel("Level_01"))
	{
		return false;
	}

	if (!this->createLevel())
	{
		return false;
	}

	for (auto iter : this->bricksObjects)
	{
		iter->initialize();
	}

	Ball* ball = new Ball("ball");
	ball->initialize();
	this->balls.push_back(ball);

	this->player = new Player("player");
	this->player->initialize();

	return true;
}

void Level::update(float deltaTime)
{
	for (auto iter : this->bricksObjects)
	{
		iter->update(deltaTime);
		checkBrickCollision(iter);
	}

	for (auto iter : this->balls)
	{
		iter->update(deltaTime);

		if (iter->getTransform().y < 0)
		{
			iter->setYVelocity(1 * BALL_SPEED * deltaTime);
		}
		else if (iter->getTransform().y > SCREEN_HEIGHT - iter->getTransform().h)
		{
			iter->setYVelocity(-1 * BALL_SPEED * deltaTime);
		}
		else if (iter->getTransform().x < 0)
		{
			iter->setXVelocity(1 * BALL_SPEED * deltaTime);
		}
		else if (iter->getTransform().x > SCREEN_WIDTH - iter->getTransform().w)
		{
			iter->setXVelocity(-1 * BALL_SPEED * deltaTime);
		}
	}

	this->player->update(deltaTime);

	checkPaddleCollision(deltaTime);
}

bool Level::loadLevel(std::string filename)
{
	std::string xmlFilename = DEFAULT_LEVEL_PATH;
	xmlFilename.append(filename).append(".xml");
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(xmlFilename.c_str());
	if (!checkXmlResult(eResult))
	{
		return false;
	}

	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr)
	{
		//std::cout << "Error creating ROOT NODE!" << std::endl;
		return false;
	}

	//-----------------------Level attributes---------------------------
	this->levelDefinition = LevelDefinition();

	tinyxml2::XMLElement* rootElement = pRoot->ToElement();
	eResult = rootElement->QueryIntAttribute("RowCount", &levelDefinition.rowCount);
	eResult = rootElement->QueryIntAttribute("ColumnCount", &levelDefinition.columnCount);
	eResult = rootElement->QueryIntAttribute("RowSpacing", &levelDefinition.rowSpacing);
	eResult = rootElement->QueryIntAttribute("ColumnSpacing", &levelDefinition.columnSpacing);
	const char* bgTexture;
	eResult = rootElement->QueryStringAttribute("BackgroundTexture", &bgTexture);
	levelDefinition.backgroundTexture = bgTexture;

	//-----------------------BrickType attributes---------------------------
	tinyxml2::XMLNode* brickTypesNode = pRoot->FirstChildElement("BrickTypes");
	tinyxml2::XMLElement* brickTypeElement = brickTypesNode->FirstChildElement("BrickType");

	while (brickTypeElement != nullptr)
	{
		BrickType* brickType = new BrickType();

		brickType->id = brickTypeElement->Attribute("Id");
		brickType->texture = brickTypeElement->Attribute("Texture");
		brickType->hitPoints = (int)brickTypeElement->Attribute("HitPoints");
		brickType->hitSound = brickTypeElement->Attribute("HitSound");
		brickType->breakSound = brickTypeElement->Attribute("BreakSound");
		brickType->breakScore = (int)brickTypeElement->Attribute("BreakScore");

		brickTypes[brickType->id] = brickType;

		brickTypeElement = brickTypeElement->NextSiblingElement("BrickType");
	}

	//-----------------------Extract bricks----------------------------
	tinyxml2::XMLElement* pElement = pRoot->FirstChildElement("Bricks");
	const char* brickArray = pElement->GetText();
	extractBricks(brickArray);

	return true;
}

bool Level::createLevel()
{
	float offsetX = 1024.f / this->levelDefinition.columnCount;
	float offsetY = 768.f / this->levelDefinition.rowCount;
	float w = offsetX - this->levelDefinition.columnSpacing;
	float h = offsetY - this->levelDefinition.rowSpacing;
	float rowSpacingOffset = this->levelDefinition.rowSpacing / 2.f;
	float columnSpacingOffset = this->levelDefinition.columnSpacing / 2.f;

	int cnt;
	int y = 0;
	std::vector< std::vector<std::string> >::iterator row;
	std::vector<std::string>::iterator col;
	for (row = this->bricks.begin(); row != this->bricks.end(); row++)
	{
		cnt = 0;
		for (col = row->begin(); col != row->end(); col++)
		{
			Brick* brick = new Brick();

			std::string brickTypeId = *col;

			if (brickTypeId != "_")
			{
				BrickType* type = this->brickTypes.find(brickTypeId)->second;
				brick->setBrickType(*type);
				brick->setTextureFilename(type->texture);
			}

			SDL_Rect rect = { (cnt * offsetX) + columnSpacingOffset, (y * offsetY) + rowSpacingOffset, w, h };
			brick->setTransform(rect);

			bricksObjects.push_back(brick);

			++cnt;
		}
		++y;
	}

	return true;
}

bool Level::checkXmlResult(tinyxml2::XMLError error)
{
	if (error != tinyxml2::XML_SUCCESS)
	{
		//std::cout << "Error: " << error << std::endl;
		return false;
	}

	return true;
}

void Level::render(SDL_Renderer* renderer)
{
	for (auto iter : this->bricksObjects)
	{
		iter->render(renderer);
	}

	for (auto iter : this->balls)
	{
		iter->render(renderer);
	}

	this->player->render(renderer);
}

void Level::destroy()
{
	for (auto brick : this->bricksObjects)
	{
		brick->destroy();
		delete brick;
		brick = NULL;
	}

	for (auto type : this->brickTypes)
	{
		delete type.second;
		type.second = NULL;
	}

	for (auto brick : this->balls)
	{
		brick->destroy();
		delete brick;
		brick = NULL;
	}

	this->bricksObjects.clear();
	this->brickTypes.clear();
	this->balls.clear();

	delete this->player;
	this->player = NULL;
}

void Level::extractBricks(const char* text)
{
	std::stringstream stream(text);
	std::string line, symbol;
	std::vector<std::string> tempArray;
	int row = 0;

	while (std::getline(stream, line))
	{
		if (line.size() < this->levelDefinition.columnCount)
		{
			continue;
		}
		else
		{
			std::stringstream lineStream;
			lineStream << line;
			while (lineStream >> symbol)
			{
				tempArray.push_back(symbol);
			}

			bricks.push_back(tempArray);
			tempArray.clear();
			++row;
		}
	}
}

void Level::checkBrickCollision(Brick* brick)
{
}

void Level::checkPaddleCollision(float deltaTime)
{
	SDL_Rect ballRect;
	for (auto iter : this->balls)
	{
		ballRect = iter->getTransform();
		// Get the center y-coordinate of the ball
		float ballCenterX = ballRect.x + (ballRect.w / 2.0f);

		// Paddle collisions
		if (this->paddleCollision(iter)) {
			this->setDirection(iter, this->getReflection(ballCenterX - this->player->getTransform().x), -1, deltaTime);
		}
	}
}

bool Level::paddleCollision(Ball* ball) {

	const SDL_Rect ballRect = ball->getTransform();
	const SDL_Rect playerRect = this->player->getTransform();

	// Check paddle bounding box against ball bounding box
	if (SDL_HasIntersection(&ballRect, &playerRect))
	{
		return true;
	}

	return false;
}

float Level::getReflection(float hitx)
{
	SDL_Rect playerRect = this->player->getTransform();

	// Make sure the hitx variable is within the width of the paddle
	if (hitx < 0) {
		hitx = 0;
	}
	else if (hitx > playerRect.w) {
		hitx = playerRect.w;
	}

	// Everything left the center of the paddle is reflected left
	// while everything right the center is reflected right
	hitx -= (float)playerRect.w / 2.0f;

	// Scale the reflection, making it fall in the range -2.0f to 2.0f
	return 2.0f * (hitx / (float)playerRect.w / 2.0f);
}

void Level::setDirection(Ball* ball, float newdirx, float newdiry, float deltaTime)
{
	// Normalize the direction vector and multiply with BALL_SPEED
	float length = sqrt(newdirx * newdirx + newdiry * newdiry);
	float x = (BALL_SPEED * (newdirx / length)) * deltaTime;
	float y = (BALL_SPEED * (newdiry / length)) * deltaTime;

	ball->setXVelocity(x);
	ball->setYVelocity(y);
}