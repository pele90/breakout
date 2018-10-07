#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>

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
};

#endif // !PLAYER_H
