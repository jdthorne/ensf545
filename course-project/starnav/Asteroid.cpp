#include "Asteroid.h"
#include "ShipMesh.h"

Asteroid::Asteroid(Vector initialPosition, double radius)
	: mesh(SHIP_MESH_POINTS)
{
	position = initialPosition;
}

Asteroid::~Asteroid(void)
{
}

void Asteroid::render(bool haptics)
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
