#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include "Resources.h"

class Ball : public Entity 
{
public:
	Ball();
	Ball(std::string filename);
	virtual ~Ball();

	virtual bool initialize();
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);
	virtual void destroy();

};

#endif // !BALL_H
