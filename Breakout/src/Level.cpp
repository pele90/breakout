#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

bool Level::initialize(std::string levelName)
{
	// PLAYER
	this->player = new Player(PLAYER_TEXTURE_NAME);
	if (!this->player->initialize())
	{
		Util::showMessageBox("Player initialization failed");
		return false;
	}

	// add sound for player and ball collision
	SoundManager::addSound(BALL_PLAYER_HIT);

	// BALL
	this->ball = new Ball(BALL_TEXTURE_NAME);
	if (!ball->initialize())
	{
		Util::showMessageBox("Ball initialization failed");
		return false;
	}

	// LEVEL
	GlobalState::setLives(DEFAULT_LIVES);
	this->isBallFollowingPlayer = true;
	if (!this->initLevel(levelName))
	{
		Util::showMessageBox("Loading level failed");
		return false;
	}

	// BRICKS
	for (auto brick : this->bricksObjects)
	{
		if (!brick->initialize())
		{
			Util::showMessageBox("Bricks initialization failed");
			return false;
		}
	}

	return true;
}

void Level::update(float deltaTime)
{
	// BRICKS
	for (auto brick : this->bricksObjects)
	{
		brick->update(deltaTime);

		if (brick->isInteractable())
		{
			checkBallBrickCollision(this->ball, brick, deltaTime);
		}
	}

	// BALL
	this->ball->update(deltaTime);

	if (this->isBallFollowingPlayer)
	{
		this->ballFollowPlayer();
	}

	// If SPACE button pressed, the ball is ejected
	if (Input::isSpaceButtonPressed())
	{
		isBallFollowingPlayer = false;
		this->ball->setFollowPlayer(isBallFollowingPlayer);
	}

	// BALL-FIELD INTERACTIONS
	this->handleBallFieldInteractions();

	// BALL
	this->player->update(deltaTime);

	// BALL-PADDLE INTERACTION
	this->checkBallPaddleCollision(deltaTime);
}

void Level::render(SDL_Renderer* renderer)
{
	// PLAYER
	this->player->render(renderer);

	// BALL
	this->ball->render(renderer);

	// BRICKS
	for (auto iter : this->bricksObjects)
	{
		iter->render(renderer);
	}
}

void Level::destroy()
{
	// PLAYER
	this->player->destroy();
	delete this->player;
	this->player = nullptr;

	// BALL
	this->ball->destroy();
	delete this->ball;
	this->ball = nullptr;

	// BRICKS
	for (auto brick : this->bricksObjects)
	{
		brick->destroy();
		delete brick;
		brick = nullptr;
	}

	// BRICK TYPES
	for (auto type : this->brickTypes)
	{
		delete type.second;
		type.second = nullptr;
	}

	this->bricksObjects.clear();
	this->brickTypes.clear();
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
	SDL_Rect ballRect = this->ball->getTransform();
	SDL_Rect playerRect = this->player->getTransform();

	ballRect.x = playerRect.x + (playerRect.w / 2);
	ballRect.y = playerRect.y - (ballRect.w);
	this->ball->setTransform(ballRect);
}

// LEVEL
bool Level::initLevel(std::string filename)
{
	std::string xmlFilename = DEFAULT_LEVEL_PATH;
	xmlFilename.append(filename).append(".xml");
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(xmlFilename.c_str());
	if (!checkXmlResult(eResult))
	{
		return false;
	}

	tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr)
	{
		Util::showMessageBox("Failed getting the root of XML doc!");
		return false;
	}

	//-----------------------Level attributes---------------------------
	LevelDefinition levelDefinition = LevelDefinition();

	tinyxml2::XMLElement* rootElement = pRoot->ToElement();
	eResult = rootElement->QueryIntAttribute(ROW_COUNT, &levelDefinition.rowCount);
	eResult = rootElement->QueryIntAttribute(COLUMN_COUNT, &levelDefinition.columnCount);
	eResult = rootElement->QueryIntAttribute(ROW_SPACING, &levelDefinition.rowSpacing);
	eResult = rootElement->QueryIntAttribute(COLUMN_SPACING, &levelDefinition.columnSpacing);
	const char* bgTexture;
	rootElement->QueryStringAttribute(BACKGROUND_TEXTURE, &bgTexture);
	levelDefinition.backgroundTexture = bgTexture;

	//-----------------------BrickType attributes---------------------------
	tinyxml2::XMLNode* brickTypesNode = pRoot->FirstChildElement(BRICK_TYPES);
	tinyxml2::XMLElement* brickTypeElement = brickTypesNode->FirstChildElement(BRICK_TYPE);

	while (brickTypeElement != nullptr)
	{
		BrickType* brickType = new BrickType();

		brickType->id = brickTypeElement->Attribute(BRICK_TYPE_ID);
		brickType->texture = brickTypeElement->Attribute(BRICK_TYPE_TEXTURE);
		brickType->hitPoints = brickTypeElement->Attribute(BRICK_TYPE_HIT_POINTS);
		brickType->hitSound = brickTypeElement->Attribute(BRICK_TYPE_HIT_SOUND);
		brickType->breakSound = brickTypeElement->Attribute(BRICK_TYPE_BREAK_SOUND) == NULL ? "": brickTypeElement->Attribute(BRICK_TYPE_BREAK_SOUND);
		brickType->breakScore = brickTypeElement->Attribute(BRICK_TYPE_BREAK_SCORE) == NULL ? "" : brickTypeElement->Attribute(BRICK_TYPE_BREAK_SCORE);

		brickTypes[brickType->id] = brickType;

		brickTypeElement = brickTypeElement->NextSiblingElement(BRICK_TYPE);
	}

	//-----------------------Extract bricks----------------------------
	tinyxml2::XMLElement* pElement = pRoot->FirstChildElement(BRICKS);
	const char* brickArray = pElement->GetText();
	extractBricks(levelDefinition, brickArray);

	if (!this->createLevel(levelDefinition))
	{
		Util::showMessageBox("Creating level failed!");
		return false;
	}

	return true;
}

bool Level::createLevel(LevelDefinition levelDefinition)
{
	float boardXOffset = (DEFAULT_SCREEN_WIDTH - DEFAULT_BOARD_WIDTH) / 2.f;
	float boardYOffset = (DEFAULT_SCREEN_HEIGHT - DEFAULT_BOARD_HEIGHT) / 2.f;
	float offsetX = DEFAULT_BOARD_WIDTH / levelDefinition.columnCount;
	float offsetY = DEFAULT_SCREEN_HEIGHT / levelDefinition.rowCount;
	float w = offsetX - levelDefinition.columnSpacing;
	float h = offsetY - levelDefinition.rowSpacing;
	float rowSpacingOffset = levelDefinition.rowSpacing / 2.f;
	float columnSpacingOffset = levelDefinition.columnSpacing / 2.f;

	int rowCounter;
	int columnCounter = 0;
	std::vector< std::vector<std::string> >::iterator row;
	std::vector<std::string>::iterator col;
	for (row = this->bricks.begin(); row != this->bricks.end(); row++)
	{
		rowCounter = 0;
		for (col = row->begin(); col != row->end(); col++)
		{
			Brick* brick = new Brick();

			std::string brickTypeId = *col;

			// if brick is any of brick type
			if (brickTypeId != EMPTY_BRICK)
			{
				BrickType* type = this->brickTypes.find(brickTypeId)->second;
				brick->setBrickType(*type);
				brick->setTextureFilename(type->texture);
				brick->setInteractable(true);

				if (type->hitPoints != INFINITE_BRICK_TYPE)
				{
					this->numOfDestroyableBricks += std::stoi(type->hitPoints);
				}
			}

			SDL_Rect rect = { ((rowCounter * offsetX) + columnSpacingOffset) + boardXOffset, ((columnCounter * offsetY) + rowSpacingOffset) + boardYOffset, w, h };
			brick->setTransform(rect);

			bricksObjects.push_back(brick);

			++rowCounter;
		}
		++columnCounter;
	}

	return true;
}

bool Level::checkXmlResult(tinyxml2::XMLError error)
{
	if (error != tinyxml2::XML_SUCCESS)
	{
		Util::showMessageBox("Error parsing XML file! Error: " + error);
		return false;
	}

	return true;
}

void Level::extractBricks(LevelDefinition levelDefinition, const char* text)
{
	std::stringstream stream(text);
	std::string line, symbol;
	std::vector<std::string> tempArray;
	int row = 0;

	while (std::getline(stream, line))
	{
		if (line.size() < (size_t)levelDefinition.columnCount)
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

// BALL-FIELD COLLISION
void Level::handleBallFieldInteractions()
{
	// TOP
	if (this->ball->getTransform().y < 0)
	{
		float y = this->ball->getVelocity().getY();
		this->ball->setYVelocity(y * -1);
	}
	// BOTTOM
	else if (this->ball->getTransform().y > DEFAULT_SCREEN_HEIGHT - this->ball->getTransform().h)
	{
		float y = this->ball->getVelocity().getY();
		this->ball->setYVelocity(y * -1);

		// If reducing life the total lives number is zero (0)
		if (GlobalState::reduceLife())
		{
			// End game and show end game screen
			GlobalState::setCurrentState(GlobalState::GameState::ShowEndScreen);
		}

		// Stick the ball to the player after the ball went behind player and hit the wall
		isBallFollowingPlayer = true;

		// Set the ball flag to stop moving in her own update
		this->ball->setFollowPlayer(isBallFollowingPlayer);

		// Set UI to be dirty so it can be redrawn again with changed values
		this->uiChanged = true;
	}
	// LEFT
	else if (this->ball->getTransform().x < 0)
	{
		float x = this->ball->getVelocity().getX();
		this->ball->setXVelocity(x * -1);
	}
	// RIGHT
	else if (this->ball->getTransform().x > DEFAULT_SCREEN_WIDTH - this->ball->getTransform().w)
	{
		float x = this->ball->getVelocity().getX();
		this->ball->setXVelocity(x * -1);
	}
}

// BALL-BRICK COLLISION
void Level::checkBallBrickCollision(Ball* ball, Brick* brick, float deltaTime)
{
	SDL_Rect ballRect = ball->getTransform();
	SDL_Rect brickRect = brick->getTransform();
	Vector2D ballVelocity = ball->getVelocity();

	float ballCenterX = ballRect.x + (ballRect.w / 2);
	float ballCenterY = ballRect.y + (ballRect.h / 2);
	float brickCenterX = brickRect.x + (brickRect.w / 2);
	float brickCenterY = brickRect.y + (brickRect.h / 2);

	// Collision detected
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

		// If there are still interactable bricks
		if (!this->winCondition())
		{
			// calculate y amount of overlap between the ball and brick
			float yMin = 0;
			if (brickRect.y > ballRect.y) {
				yMin = brickRect.y;
			}
			else {
				yMin = ballRect.y;
			}

			float yMax = 0;
			if (brickRect.y + brickRect.h < ballRect.y + ballRect.h) {
				yMax = brickRect.y + brickRect.h;
			}
			else {
				yMax = ballRect.y + ballRect.h;
			}
			// amount of ball penetration into brick on Y axis
			float ySize = yMax - yMin; 

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
			// amount of ball penetration into brick on X axis
			float xSize = xMax - xMin;

			// Set collision response based on point of collision
			if (xSize > ySize) {
				if (ballCenterY > brickCenterY) {
					// Bottom
					ballRect.y += ySize + 1.f; // Move out of collision
					this->ballBrickResponse(Brick::BrickCollisionResponse::Bottom, ball, deltaTime);
				}
				else {
					// Top
					ballRect.y -= ySize + 1.f; // Move out of collision
					this->ballBrickResponse(Brick::BrickCollisionResponse::Top, ball, deltaTime);
				}
			}
			else {
				if (ballCenterX < brickCenterX) {
					// Left
					ballRect.x -= xSize + 1.f; // Move out of collision
					this->ballBrickResponse(Brick::BrickCollisionResponse::Left, ball, deltaTime);
				}
				else {
					// Right
					ballRect.x += xSize + 1.f; // Move out of collision
					this->ballBrickResponse(Brick::BrickCollisionResponse::Right, ball, deltaTime);
				}
			}
		}
	}
}

void Level::ballBrickResponse(Brick::BrickCollisionResponse value, Ball* ball, float deltaTime)
{
	// Direction factors
	int mulX = 1;
	int mulY = 1;

	// caching velocity values
	float xVelocity = ball->getVelocity().getX();
	float yVelocity = ball->getVelocity().getY();

	if (xVelocity > 0) 
	{
		// Ball is moving in the positive x direction
		if (yVelocity > 0)
		{
			// Ball is moving in the positive y direction
			// +1 +1
			if (value == Brick::BrickCollisionResponse::Left || value == Brick::BrickCollisionResponse::Bottom) 
			{
				mulX = -1;
			}
			else 
			{
				mulY = -1;
			}
		}
		else if (yVelocity < 0) 
		{
			// Ball is moving in the negative y direction
			// +1 -1
			if (value == Brick::BrickCollisionResponse::Left || value == Brick::BrickCollisionResponse::Top) 
			{
				mulX = -1;
			}
			else 
			{
				mulY = -1;
			}
		}
	}
	else if (xVelocity < 0) 
	{
		// Ball is moving in the negative x direction
		if (yVelocity > 0) 
		{
			// Ball is moving in the positive y direction
			// -1 +1
			if (value == Brick::BrickCollisionResponse::Right || value == Brick::BrickCollisionResponse::Bottom) 
			{
				mulX = -1;
			}
			else 
			{
				mulY = -1;
			}
		}
		else if (yVelocity < 0) 
		{
			// Ball is moving in the negative y direction
			// -1 -1
			if (value == Brick::BrickCollisionResponse::Right || value == Brick::BrickCollisionResponse::Top) 
			{
				mulX = -1;
			}
			else
			{
				mulY = -1;
			}
		}
	}

	// Set the new direction of the ball, by multiplying the old direction
	// with the determined direction factors
	this->setDirection(ball, mulX * xVelocity, mulY * yVelocity, deltaTime);
}

// BALL-PADDLE COLLISION
void Level::checkBallPaddleCollision(float deltaTime)
{
	SDL_Rect ballRect = ball->getTransform();
	const SDL_Rect playerRect = this->player->getTransform();

	// Get the center y-coordinate of the ball
	float ballCenterX = ballRect.x + (ballRect.w / 2.0f);

	// Check paddle bounding box against ball bounding box
	if (SDL_HasIntersection(&ballRect, &playerRect))
	{
		SoundManager::playSFX(BALL_PLAYER_HIT);

		this->setDirection(this->ball, this->getCollisionReflection(ballCenterX - this->player->getTransform().x), -1, deltaTime);
	}
}

float Level::getCollisionReflection(float hitX)
{
	SDL_Rect playerRect = this->player->getTransform();

	// Make sure the hitx variable is within the width of the paddle
	if (hitX < 0) {
		hitX = 0;
	}
	else if (hitX > playerRect.w) {
		hitX = playerRect.w;
	}

	// Everything left the center of the paddle is reflected left
	// while everything right the center is reflected right
	hitX -= (float)playerRect.w / 2.0f;

	// Scale the reflection, making it fall in the range -2.0f to 2.0f
	return 2.0f * (hitX / (float)playerRect.w / 2.0f);
}

void Level::setDirection(Ball* ball, float newdirx, float newdiry, float deltaTime)
{
	// Normalize the direction vector and multiply with BALL_MOVEMENT_SPEED
	float length = sqrt(newdirx * newdirx + newdiry * newdiry);
	float x = (BALL_MOVEMENT_SPEED * (newdirx / length)) * deltaTime;
	float y = (BALL_MOVEMENT_SPEED * (newdiry / length)) * deltaTime;

	ball->setXVelocity(x);
	ball->setYVelocity(y);
}

// GAMEPLAY
bool Level::winCondition()
{
	// if all destroyable bricks are destroyed
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