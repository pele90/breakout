#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include "Vector2D.h"
#include "Resources.h"

#define BALL_SPEED 600

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

	Vector2D getVelocity() const;
	void setXVelocity(float value);
	void setYVelocity(float value);
	void setFollowPlayer(bool value);

private:
	Vector2D velocity;
	bool followPlayer;
};

#endif // !BALL_H
