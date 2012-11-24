#include "Ship.h"
#include "ShipMesh.h"
#include "Quaternion.h"
#include "RenderHelpers.h"

#include <windows.h>

Ship::Ship(void)
	: mesh(SHIP_MESH_POINTS)
	, orientation(Quaternion::SPIN_X)
	, exploded(false)
{
	position = Vector(0, 0, -7);
	radius = 0.2;
}

Ship::~Ship(void)
{
}

void Ship::render(bool haptics)
{
	glShadeModel(GL_FLAT);
	glColor3f(0.7, 0.7, 0.7);

	if (position.z > 8.5)
	{
		exploded = true;
	}

	glPushMatrix();

	glTranslatev(position);

	if (velocity.magnitude() > 0.0001)
	{
		Quaternion instantOrientation = Vector(0, 1, 0).rotationTo(velocity);
		orientation = Quaternion::slerp(orientation, instantOrientation, 0.95);
	}
	glRotateq(orientation);
	glScalef(1.5, 3, 1.5);

	if (haptics)
	{
		mesh.renderHaptics(Vector(0,0,0), radius, hapticId);
	}
	else
	{
		mesh.render(Vector(0,0,0), radius);
	}

	glPopMatrix();
}

void Ship::handleCollision()
{
	exploded = true;
}

void Ship::push(Vector newPosition)
{
	velocity = Vector(0, 0, 0);
	Vector change = newPosition - position;
	if (change.magnitude() > 0.001)
	{
		Quaternion instantOrientation = Vector(0, 1, 0).rotationTo(change.normalized());
		orientation = Quaternion::slerp(orientation, instantOrientation, 0.9)	;
	}

	position = newPosition;
}
