#include "Input.h"

Input& Input::getInstance()
{
	static Input instance;
	return instance;
}

bool Input::isLeftMouseButtonUp()
{
	return leftMouseButtonPressed;
}

bool Input::isRightMouseButtonUp()
{
	return rightMouseButtonPressed;
}

bool Input::isRightArrowPressed()
{
	return rightArrowPressed;
}

bool Input::isLeftArrowPressed()
{
	return leftArrowPressed;
}

bool Input::isQButtonPressed()
{
	return qButtonPressed;
}

bool Input::isSpaceButtonPressed()
{
	return spaceButtonPressed;
}

void Input::setLeftMouseButtonUp(bool value)
{
	leftMouseButtonPressed = value;
}

void Input::setRightMouseButtonUp(bool value)
{
	rightMouseButtonPressed = value;
}

void Input::setRightArrowPressed(bool value)
{
	rightArrowPressed = value;
}

void Input::setLeftArrowPressed(bool value)
{
	leftArrowPressed = value;
}

void Input::setQButtonPressed(bool value)
{
	qButtonPressed = value;
}

void Input::setSpaceButtonPressed(bool value)
{
	spaceButtonPressed = value;
}

void Input::setMouse(int x, int y)
{
	mouse.x = x;
	mouse.y = y;
}

void Input::getMouse(int& x, int& y)
{
	x = mouse.x;
	y = mouse.y;
}

void Input::reset()
{
	leftMouseButtonPressed = false;
	rightMouseButtonPressed = false;
	leftArrowPressed = false;
	rightArrowPressed = false;
	qButtonPressed = false;
	spaceButtonPressed = false;
}

bool Input::handleInputs()
{
	reset();

	bool isRunning = true;
	SDL_Event e;
	const Uint8* currentKeyStates;
	while (SDL_PollEvent(&e) != 0)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		setMouse(x, y);

		switch (e.type)
		{
		case SDL_QUIT:
		{
			isRunning = false;
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				setLeftMouseButtonUp(true);
			}
			else if (e.button.button == SDL_BUTTON_RIGHT)
			{
				setRightMouseButtonUp(true);
			}
			break;
		}
		}
	}

	currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		setLeftArrowPressed(true);
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		setRightArrowPressed(true);
	}
	else if (currentKeyStates[SDL_SCANCODE_Q])
	{
		setQButtonPressed(true);
	}
	else if (currentKeyStates[SDL_SCANCODE_SPACE])
	{
		setSpaceButtonPressed(true);
	}

	return isRunning;
}

// A quirk of C++, static member variables need to be instantiated outside of the class
Input::Mouse Input::mouse;
bool Input::leftMouseButtonPressed;
bool Input::rightMouseButtonPressed;
bool Input::leftArrowPressed;
bool Input::rightArrowPressed;
bool Input::qButtonPressed;
bool Input::spaceButtonPressed;