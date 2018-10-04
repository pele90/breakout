#include "Input.h"

Input* Input::instance = 0;

Input* Input::getInstance()
{
	if (instance == 0)
	{
		instance = new Input();
	}

	return instance;
}

bool Input::isLeftMouseButtonPressed()
{
	return leftMouseButtonPressed;
}

bool Input::isRightMouseButtonPressed()
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

void Input::setLeftMouseButtonPressed(bool value)
{
	leftMouseButtonPressed = value;
}

void Input::setRightMouseButtonPressed(bool value)
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
}

// A quirk of C++, static member variables need to be instantiated outside of the class
Input::Mouse Input::mouse;
bool Input::leftMouseButtonPressed;
bool Input::rightMouseButtonPressed;
bool Input::leftArrowPressed;
bool Input::rightArrowPressed;