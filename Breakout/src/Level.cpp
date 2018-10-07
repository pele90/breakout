#include "Level.h"
#include <sstream>

Level::Level()
{
}

Level::~Level()
{
}

bool Level::initialize(std::string levelName)
{
	if (!this->loadLevel(levelName))
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
	
	GlobalState::setLives(DEFAULT_LIVES);
	this->isBallFollowingPlayer = true;

	return true;
}

void Level::update(float deltaTime)
{
	for (auto brick : this->bricksObjects)
	{
		brick->update(deltaTime);

		if (brick->isInteractable())
		{
			checkBrickCollision(this->balls[0], brick, deltaTime);
		}
	}

	for (auto iter : this->balls)
	{
		iter->update(deltaTime);

		if (this->isBallFollowingPlayer)
		{
			this->ballFollowPlayer();
		}

		if (Input::isSpaceButtonPressed())
		{
			isBallFollowingPlayer = false;
			iter->setFollowPlayer(isBallFollowingPlayer);
		}

		if (iter->getTransform().y < 0)
		{
			float i = iter->getVelocity().getY();
			iter->setYVelocity(i * - 1);
		}
		else if (iter->getTransform().y > DEFAULT_SCREEN_HEIGHT - iter->getTransform().h)
		{
			float i = iter->getVelocity().getY();
			iter->setYVelocity(i * -1);

			// Ball went behind player, remove one life
			// If there is no more lives, end game
			if (GlobalState::reduceLife())
			{
				GlobalState::setCurrentState(GlobalState::GameState::ShowEndScreen);
			}

			isBallFollowingPlayer = true;
			iter->setFollowPlayer(isBallFollowingPlayer);
			this->uiChanged = true;
		}
		else if (iter->getTransform().x < 0)
		{
			float i = iter->getVelocity().getX();
			iter->setXVelocity(i * -1);
		}
		else if (iter->getTransform().x > DEFAULT_SCREEN_WIDTH - iter->getTransform().w)
		{
			float i = iter->getVelocity().getX();
			iter->setXVelocity(i * -1);
		}
	}

	this->player->update(deltaTime);

	this->checkPaddleCollision(deltaTime);
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
		brickType->hitPoints = brickTypeElement->Attribute("HitPoints");
		brickType->hitSound = brickTypeElement->Attribute("HitSound");
		brickType->breakSound = brickTypeElement->Attribute("BreakSound") == NULL ? "": brickTypeElement->Attribute("BreakSound");
		brickType->breakScore = brickTypeElement->Attribute("BreakScore") == NULL ? "" : brickTypeElement->Attribute("BreakScore");

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
	float boardXOffset = (DEFAULT_SCREEN_WIDTH - DEFAULT_BOARD_WIDTH) / 2;
	float boardYOffset = (DEFAULT_SCREEN_HEIGHT - DEFAULT_BOARD_HEIGHT) / 2;
	float offsetX = DEFAULT_BOARD_WIDTH / this->levelDefinition.columnCount;
	float offsetY = DEFAULT_SCREEN_HEIGHT / this->levelDefinition.rowCount;
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

			// if brick is any of brick type
			if (brickTypeId != "_")
			{
				BrickType* type = this->brickTypes.find(brickTypeId)->second;
				brick->setBrickType(*type);
				brick->setTextureFilename(type->texture);
				brick->setInteractable(true);
				this->numOfDestroyableBricks++;
			}

			SDL_Rect rect = { ((cnt * offsetX) + columnSpacingOffset) + boardXOffset, ((y * offsetY) + rowSpacingOffset) + boardYOffset, w, h };
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

void Level::checkBrickCollision(Ball* ball, Brick* brick, float deltaTime)
{
	SDL_Rect ballRect = ball->getTransform();
	SDL_Rect brickRect = brick->getTransform();
	Vector2D ballVelocity = ball->getVelocity();

	float ballCenterX = ballRect.x + (ballRect.w / 2);
	float ballCenterY = ballRect.y + (ballRect.h / 2);
	float brickCenterX = brickRect.x + (brickRect.w / 2);
	float brickCenterY = brickRect.y + (brickRect.h / 2);

	// Collision detected; do all the stuff for that like remove life, play sound, destroy brick, etc.
	if (ballRect.x <= brickRect.x + brickRect.w &&
		ballRect.x + ballRect.w >= brickRect.x &&
		ballRect.y <= brickRect.y + brickRect.h &&
		ballRect.y + ballRect.h >= brickRect.y)
	{
		/////--------------------- BALL HIT THE BRICK------------------------
		int hitResult = brick->handleHit();
		if (hitResult != -1)
		{
			GlobalState::addScore(hitResult);
			this->uiChanged = true;
			this->numOfDestroyableBricks--;
		}

		if (!this->winCondition())
		{
			// calculate y amount of overlap
			float ymin = 0;
			if (brickRect.y > ballRect.y) {
				ymin = brickRect.y;
			}
			else {
				ymin = ballRect.y;
			}
			float ymax = 0;

			if (brickRect.y + brickRect.h < ballRect.y + ballRect.h) {
				ymax = brickRect.y + brickRect.h;
			}
			else {
				ymax = ballRect.y + ballRect.h;
			}
			float ySize = ymax - ymin;

			// Calculate x amount of overlap
			float xMin = 0;
			if (brickRect.x > ballRect.x) {
				xMin = brickRect.x;
			}
			else {
				xMin = ballRect.x;
			}

			float xMax = 0;
			if (brickRect.x + brickRect.w < ballRect.x + ballRect.w) {
				xMax = brickRect.x + brickRect.w;
			}
			else {
				xMax = ballRect.x + ballRect.w;
			}

			float xSize = xMax - xMin;

			// The origin is at the top-left corner of the screen!
			// Set collision response
			if (xSize > ySize) {
				if (ballCenterY > brickCenterY) {
					// Bottom
					ballRect.y += ySize + 0.01f; // Move out of collision
					this->ballBrickResponse(Brick::BrickResponse::Bottom, ball, deltaTime);
				}
				else {
					// Top
					ballRect.y -= ySize + 0.01f; // Move out of collision
					this->ballBrickResponse(Brick::BrickResponse::Top, ball, deltaTime);
				}
			}
			else {
				if (ballCenterX < brickCenterX) {
					// Left
					ballRect.x -= xSize + 0.01f; // Move out of collision
					this->ballBrickResponse(Brick::BrickResponse::Left, ball, deltaTime);
				}
				else {
					// Right
					ballRect.x += xSize + 0.01f; // Move out of collision
					this->ballBrickResponse(Brick::BrickResponse::Right, ball, deltaTime);
				}
			}
		}
	}
}

void Level::ballBrickResponse(Brick::BrickResponse value, Ball* ball, float deltaTime)
{
	// BrickResponse 0: Left, 1: Top, 2: Right, 3: Bottom

	// Direction factors
	int mulX = 1;
	int mulY = 1;
	float xVelocity = ball->getVelocity().getX();
	float yVelocity = ball->getVelocity().getY();

	if (xVelocity > 0) {
		// Ball is moving in the positive x direction
		if (yVelocity > 0) {
			// Ball is moving in the positive y direction
			// +1 +1
			if (value == Brick::BrickResponse::Left || value == Brick::BrickResponse::Bottom) {
				mulX = -1;
			}
			else {
				mulY = -1;
			}
		}
		else if (yVelocity < 0) {
			// Ball is moving in the negative y direction
			// +1 -1
			if (value == Brick::BrickResponse::Left || value == Brick::BrickResponse::Top) {
				mulX = -1;
			}
			else {
				mulY = -1;
			}
		}
	}
	else if (xVelocity < 0) {
		// Ball is moving in the negative x direction
		if (yVelocity > 0) {
			// Ball is moving in the positive y direction
			// -1 +1
			if (value == Brick::BrickResponse::Right || value == Brick::BrickResponse::Bottom) {
				mulX = -1;
			}
			else {
				mulY = -1;
			}
		}
		else if (yVelocity < 0) {
			// Ball is moving in the negative y direction
			// -1 -1
			if (value == Brick::BrickResponse::Right || value == Brick::BrickResponse::Top) {
				mulX = -1;
			}
			else {
				mulY = -1;
			}
		}
	}

	// Set the new direction of the ball, by multiplying the old direction
	// with the determined direction factors
	this->setDirection(ball, mulX * xVelocity, mulY * yVelocity, deltaTime);
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

bool Level::winCondition()
{
	if (this->numOfDestroyableBricks == 0)
	{
		if (GlobalState::getLevel() != NUMBER_OF_LEVELS)
		{
			GlobalState::setCurrentState(GlobalState::GameState::NextLevel);
		}
		else
		{
			GlobalState::setCurrentState(GlobalState::GameState::ShowEndScreen);
		}
		return true;
	}

	return false;
}

bool Level::isUiChanged() const
{
	return this->uiChanged;
}

void Level::setUiChanged(bool value)
{
	this->uiChanged = value;
}

void Level::ballFollowPlayer()
{
	SDL_Rect ballRect = this->balls[0]->getTransform();
	SDL_Rect playerRect = this->player->getTransform();

	ballRect.x = playerRect.x + (playerRect.w / 2);
	ballRect.y = playerRect.y - (ballRect.w);
	this->balls[0]->setTransform(ballRect);
}