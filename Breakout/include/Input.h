#ifndef INPUT_H
#define INPUT_H

class Input
{
public:
	struct Mouse
	{
		int x;
		int y;
	};

public:
	static Input* getInstance();
	static bool isLeftMouseButtonPressed();
	static bool isRightMouseButtonPressed();
	static bool isRightArrowPressed();
	static bool isLeftArrowPressed();

	static void setLeftMouseButtonPressed(bool value);
	static void setRightMouseButtonPressed(bool value);
	static void setRightArrowPressed(bool value);
	static void setLeftArrowPressed(bool value);

	static void setMouse(int x, int y);
	static void getMouse(int& x, int& y);

	static void reset();

private:
	Input() {}

private:
	static Input* instance;
	static Mouse mouse;
	static bool leftMouseButtonPressed;
	static bool rightMouseButtonPressed;
	static bool leftArrowPressed;
	static bool rightArrowPressed;
};

#endif // !INPUT_H
