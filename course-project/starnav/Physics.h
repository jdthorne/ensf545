#pragma once

#include <vector>

#include "Vector.h"

class Physics
{
public:
	Physics(void);
	~Physics(void);

	void simulate(std::vector<Physics*>& collidableObjects);
	void simulateHaptics();

	virtual void render(bool haptics) = 0;
	virtual void handleCollision();

	bool collidesWith(Physics& other);
	bool collidesWithAny(std::vector<Physics*>& collidableObjects);

private:
	void handleTouch(Vector cursorPosition, Vector devicePosition);

protected:
	Vector position;
	Vector velocity;
	Vector lastVelocity;

	bool hapticEffectIsRunning;

	unsigned int hapticId;
	unsigned int effectId;
	double radius;
};
