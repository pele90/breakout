#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

class Input
{
public:
	struct Mouse
	{
		int x;
		int y;
	};

public:
	static Input& getInstance();
	static bool isLeftMouseButtonUp();
	static bool isRightMouseButtonUp();
	static bool isRightArrowPressed();
	static bool isLeftArrowPressed();
	static bool isQButtonPressed();
	static bool isSpaceButtonPressed();

	static void setLeftMouseButtonUp(bool value);
	static void setRightMouseButtonUp(bool value);
	static void setRightArrowPressed(bool value);
	static void setLeftArrowPressed(bool value);
	static void setQButtonPressed(bool value);
	static void setSpaceButtonPressed(bool value);

	

	static void setMouse(int x, int y);
	static void getMouse(int& x, int& y);

	static void reset();
	static bool handleInputs();

private:
	Input() {}

	/* Explicitly disallow copying. */
	Input(const Input&);
	Input& operator= (const Input&);

private:
	static Mouse mouse;
	static bool leftMouseButtonPressed;
	static bool rightMouseButtonPressed;
	static bool leftArrowPressed;
	static bool rightArrowPressed;
	static bool qButtonPressed;
	static bool spaceButtonPressed;
};

#endif // !INPUT_H
