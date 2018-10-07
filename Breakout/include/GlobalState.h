#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#define DEFAULT_SCORE 0
#define DEFAULT_LIVES 3
#define DEFAULT_LEVEL 1
#define NUMBER_OF_LEVELS 5
#define PLAYER_STARTING_POSITION { 400, 650, 200, 20 }
#define DEFAULT_SCREEN_WIDTH 1024
#define DEFAULT_SCREEN_HEIGHT 768
#define DEFAULT_BOARD_WIDTH 924
#define DEFAULT_BOARD_HEIGHT 668
#define FPS 60;
constexpr int screen_ticks_per_frame = 1000 / FPS;

class GlobalState
{
public:
	enum GameState
	{
		Uninitialized,
		ShowSplash,
		ShowMenu,
		Play,
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
	static void nextLevel();

private:
	GlobalState() {};

	/* Explicitly disallow copying. */
	GlobalState(const GlobalState&);
	GlobalState& operator= (const GlobalState&);

private:
	static GlobalState* instance;
	static int screenWidth;
	static int screenHeight;
	static int score;
	static int lives;
	static int level;
	static GameState currentState;
};

#endif // !GLOBAL_STATE_H
