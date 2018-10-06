#include "UIObject.h"

UIObject::UIObject(){}

UIObject::UIObject(SDL_Rect rect): transform(rect){}

UIObject::~UIObject(){}

void UIObject::setTransform(SDL_Rect rect)
{
	this->transform = rect;
}

void UIObject::setName(std::string name)
{
	this->name = name;
}

std::string UIObject::getName() const
{
	return this->name;
}