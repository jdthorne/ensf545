#include "Physics.h"
#define WIN32
#include <HL/hl.h>

Physics::Physics(void)
	: radius(1)
{
	hapticId = hlGenShapes(1);
	effectId = hlGenEffects(1);
}

Physics::~Physics(void)
{
}

void Physics::simulate(std::vector<Physics*>& collidableObjects)
{
	// Basic Kinematics
	collided = false;
	position += velocity;
	velocity = velocity * 0.995;

	// Haptic Touch
	HLdouble pos[3];
	hlGetDoublev(HL_PROXY_POSITION, pos);

	Vector cursorPosition = Vector(pos[0], pos[1], pos[2]);

	HLboolean touching;
	hlGetShapeBooleanv(hapticId, HL_PROXY_IS_TOUCHING, &touching);
	if (touching)
	{
		handleTouch(cursorPosition);
	}

	hlStopEffect(effectId);
	Vector cursorOffset = cursorPosition - position;
	if (cursorOffset.magnitude() < radius)
	{
		cursorOffset = cursorOffset.normalized();

		double direction[3] = { cursorOffset.x(), cursorOffset.y(), cursorOffset.z() };
		hlEffectdv(HL_EFFECT_PROPERTY_DIRECTION, direction);
		hlEffectd(HL_EFFECT_PROPERTY_MAGNITUDE, 10);

		hlStartEffect(HL_EFFECT_CONSTANT, effectId);
		handleTouch(cursorPosition);
	}

	// Collisions
	for (unsigned int i = 0; i < collidableObjects.size(); i++)
	{
		Physics& other = *collidableObjects[i];

		if (collidableObjects[i] == this)
		{
			continue;
		}

		Vector offset = position - other.position;
		double distance = offset.magnitude();

		double collisionDistance = radius + other.radius;

		if (distance < collisionDistance && !other.collided)
		{
			collided = true;
			other.collided = true;

			Vector swap = velocity;
			velocity = other.velocity;
			other.velocity = swap;
		}
	}
}

void Physics::handleTouch(Vector cursorPosition)
{
	Vector cursorToCenter = (position - cursorPosition).normalized();

	//velocity += (cursorToCenter * 0.0001);
}
