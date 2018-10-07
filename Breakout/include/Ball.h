#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include "Vector2D.h"

class Ball : public Entity
{
public:
	Ball();
	Ball(std::string filename);
	virtual ~Ball();

	virtual bool initialize();
	virtual void update(float deltaTime);

	Vector2D getVelocity() const;
	void setXVelocity(float value);
	void setYVelocity(float value);
	void setFollowPlayer(bool value);

private:
	Vector2D velocity;
	bool followPlayer;
};

#endif // !BALL_H
