#include "GlobalState.h"

GlobalState* GlobalState::instance = 0;

GlobalState* GlobalState::getInstance()
{
	if (instance == 0)
	{
		instance = new GlobalState();
	}

	return instance;
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

// A quirk of C++, static member variables need to be instantiated outside of the class
int GlobalState::score = DEFAULT_SCORE;
int GlobalState::lives = DEFAULT_LIVES;
int GlobalState::level = DEFAULT_LEVEL;
GlobalState::GameState GlobalState::currentState = GlobalState::GameState::Uninitialized;