#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#define DEFAULT_SCORE 0
#define DEFAULT_LIVES 3
#define DEFAULT_LEVEL 1
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
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
		Restart,
		Exit,
		ShowEndScreen
	};

public:
	static GlobalState& getInstance();

	static void setScore(int value);
	static void setLives(int value);
	static void setLevel(int value);
	static void setCurrentState(GameState state);

	static int getScore();
	static int getLives();
	static int getLevel();
	static GameState getCurrentState();


private:
	GlobalState() {};

	/* Explicitly disallow copying. */
	GlobalState(const GlobalState&);
	GlobalState& operator= (const GlobalState&);

private:
	static GlobalState* instance;
	static int score;
	static int lives;
	static int level;
	static GameState currentState;
};

#endif // !GLOBAL_STATE_H
