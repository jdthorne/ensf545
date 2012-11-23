#pragma once

#include <vector>

#include "Vector.h"

class Physics
{
public:
	Physics(void);
	~Physics(void);

	void simulate(std::vector<Physics*>& collidableObjects);

	virtual void render(bool haptics) = 0;

private:
	void handleTouch(Vector cursorPosition);

protected:
	Vector position;
	Vector velocity;

	bool collided;

	unsigned int hapticId;
	unsigned int effectId;
	double radius;
};
