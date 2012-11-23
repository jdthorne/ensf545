#include "Ship.h"
#include "ShipMesh.h"

Ship::Ship(void)
	: mesh(SHIP_MESH_POINTS)
{
	velocity = Vector(0.0002, 0, 0);
}

Ship::~Ship(void)
{
}

void Ship::render(bool haptics)
{
	if (haptics)
	{
		mesh.renderHaptics(position, hapticId);
	}
	else
	{
		mesh.render(position);
	}
}
