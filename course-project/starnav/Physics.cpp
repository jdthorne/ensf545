
#include <cmath>
#include "Physics.h"
#define WIN32
#include <HL/hl.h>
#include "Starnav.h"

Physics::Physics(void)
	: radius(1)
	, position(0, 0, 0)
	, velocity(0, 0, 0)
	, hapticEffectIsRunning(false)
{
	hapticId = hlGenShapes(1);
	effectId = hlGenEffects(1);
}

Physics::~Physics(void)
{
}

void Physics::simulateHaptics()
{
	lastVelocity = velocity;

	// Haptic Touch
	HLdouble pos[3];
	hlGetDoublev(HL_PROXY_POSITION, pos);
	Vector cursorPosition = Vector(pos[0], pos[1], pos[2]);

	HLdouble devicePos[3];
	hlGetDoublev(HL_DEVICE_POSITION, devicePos);
	Vector devicePosition = Vector(devicePos[0], devicePos[1], devicePos[2]);

	HLboolean touching;
	hlGetShapeBooleanv(hapticId, HL_PROXY_IS_TOUCHING, &touching);
	if (touching)
	{
		handleTouch(cursorPosition, devicePosition);
		return;
	}

	Vector cursorOffset = cursorPosition - position;
	Vector targetPoint = devicePosition + (cursorOffset.normalized() * radius * 200);

	HLdouble target[3] = { targetPoint.x, targetPoint.y, targetPoint.z };
	hlEffectd(HL_EFFECT_PROPERTY_MAGNITUDE, 0.3);
	hlEffectd(HL_EFFECT_PROPERTY_GAIN, 0.5);
	hlEffectdv(HL_EFFECT_PROPERTY_POSITION, target);

	if (cursorOffset.magnitude() < radius * 0.9)
	{
		if (hapticEffectIsRunning)
		{
			hlUpdateEffect(effectId);
		}
		else
		{
			hlStartEffect(HL_EFFECT_SPRING, effectId);
		}
		handleTouch(cursorPosition, position - (cursorOffset.normalized() * radius));
		hapticEffectIsRunning = true;
	}
	else if (cursorOffset.magnitude() > radius * 1.1)
	{
		if (hapticEffectIsRunning)
		{
			hlStopEffect(effectId);
		}
		hapticEffectIsRunning = false;
	}
}

void Physics::simulate(std::vector<Physics*>& collidableObjects)
{
	// Basic Kinematics
	position += velocity;

	velocity = velocity * 0.999;

	// Collisions
	for (unsigned int i = 0; i < collidableObjects.size(); i++)
	{
		Physics& other = *collidableObjects[i];

		if (collidesWith(other))
		{
			double mass = pow(radius, 3);
			double otherMass = pow(other.radius, 3);

			double totalMomentum = (velocity.magnitude() * mass)
								   + (other.velocity.magnitude() * otherMass) * 1.2;

			Vector away = (position - other.position).normalized();
			double shareOfMomentum = mass / (mass + otherMass);

			velocity = away * ((totalMomentum * shareOfMomentum) / mass);

			handleCollision();
		}
	}
}
bool Physics::collidesWith(Physics& other)
{
	if (&other == this)
	{
		return false;
	}

	Vector offset = position - other.position;
	double distance = offset.magnitude();

	double collisionDistance = radius + other.radius;

	return (distance < collisionDistance);
}

bool Physics::collidesWithAny(std::vector<Physics*>& collidableObjects)
{
	for (unsigned int i = 0; i < collidableObjects.size(); i++)
	{
		if (collidesWith(*collidableObjects[i]))
		{
			return true;
		}
	}
	return false;
}

void Physics::handleTouch(Vector cursorPosition, Vector devicePosition)
{
	Vector push = devicePosition - cursorPosition;
	if (push.magnitude() == 0)
	{
		return;
	}

	velocity += (push * 0.002);
}

void Physics::handleCollision()
{
	// Do nothing
}
