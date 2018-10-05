#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Resources.h"

class Player : public Entity
{
public:
	Player();
	Player(std::string filename);
	virtual ~Player();

	virtual bool initialize();
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);
	virtual void destroy();

private:

};

#endif // !PLAYER_H
