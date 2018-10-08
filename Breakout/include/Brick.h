#ifndef BRICK_H
#define BRICK_H

#include "Entity.h"

struct BrickType
{
	std::string id;
	std::string texture;
	std::string hitPoints;
	std::string hitSound;
	std::string breakSound;
	std::string breakScore;
};

class Brick : public Entity
{
public:
	enum BrickCollisionResponse
	{
		Left,
		Top,
		Right,
		Bottom
	};
public:
	Brick();
	Brick(std::string filename);
	virtual ~Brick();
	
	virtual bool initialize();
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);

	bool isInteractable() const;
	BrickType getBrickType() const;
	void setInteractable(bool value);
	void setBrickType(BrickType type);
	int handleHit();
	void removeTexture();

private:
	BrickType brickType;
	int hitpoints;
	int breakScore;
	bool interactable;
};

#endif // !BRICK_H
