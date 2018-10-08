#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#include "Constants.h"

class GlobalState
{
public:
	enum GameState
	{
		Uninitialized,
		ShowSplash,
		ShowMenu,
		Play,
		Paused,
		NextLevel,
		Restart,
		Exit,
		ShowEndScreen
	};

public:
	static GlobalState& getInstance();

	static void setScreenWidth(int value);
	static void setScreenHeight(int value);
	static void setScore(int value);
	static void setLives(int value);
	static void setLevel(int value);
	static void setCurrentState(GameState state);

	static int getScreenWidth();
	static int getScreenHeight();
	static int getScore();
	static int getLives();
	static int getLevel();
	static GameState getCurrentState();

	static void addScore(int value);
	static bool reduceLife();
	static bool nextLevel();

private:
	GlobalState() {};

	/* Explicitly disallow copying. */
	GlobalState(const GlobalState&);
	GlobalState& operator= (const GlobalState&);

private:
	static int screenWidth;
	static int screenHeight;
	static int score;
	static int lives;
	static int level;
	static GameState currentState;
};

#endif // !GLOBAL_STATE_H
