#include "GlobalState.h"

GlobalState& GlobalState::getInstance()
{
	static GlobalState instance;
	return instance;
}

void GlobalState::setScreenWidth(int value)
{
	screenWidth = value;
}

void GlobalState::setScreenHeight(int value)
{
	screenHeight = value;
}

void GlobalState::setScore(int value)
{
	score = value;
}

void GlobalState::setLives(int value)
{
	lives = value;
}

void GlobalState::setLevel(int value)
{
	level = value;
}

void GlobalState::setCurrentState(GameState state)
{
	currentState = state;
}

int GlobalState::getScreenWidth()
{
	return screenWidth;
}

int GlobalState::getScreenHeight()
{
	return screenHeight;
}

int GlobalState::getScore()
{
	return score;
}

int GlobalState::getLives()
{
	return lives;
}

int GlobalState::getLevel()
{
	return level;
}

GlobalState::GameState GlobalState::getCurrentState()
{
	return currentState;
}

void GlobalState::addScore(int value)
{
	score += value;
}

bool GlobalState::reduceLife()
{
	lives--;
	if (lives == 0)
	{
		return true;
	}

	return false;
}

void GlobalState::nextLevel()
{
	if (++level > NUMBER_OF_LEVELS)
	{
		level = 1;
		score = 0;
	}
}

// A quirk of C++, static member variables need to be instantiated outside of the class
int GlobalState::screenWidth = DEFAULT_SCREEN_WIDTH;
int GlobalState::screenHeight = DEFAULT_SCREEN_HEIGHT;
int GlobalState::score = DEFAULT_SCORE;
int GlobalState::lives = DEFAULT_LIVES;
int GlobalState::level = DEFAULT_LEVEL;
GlobalState::GameState GlobalState::currentState = GlobalState::GameState::Uninitialized;