#include "UIObject.h"

UIObject::UIObject(){}

UIObject::UIObject(SDL_Rect rect): transform(rect){}

UIObject::~UIObject(){}

void UIObject::addChild(UIObject* child)
{
	this->child = child;
}

void UIObject::setTransform(SDL_Rect rect)
{
	this->transform = rect;
}