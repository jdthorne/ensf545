#include "Asteroid.h"
#include "ShipMesh.h"

#include <GL/glut.h>

Asteroid::Asteroid(Vector initialPosition, double initialRadius)
	: mesh(ASTEROID_MESH_POINTS)
{
	position = initialPosition;
	radius = initialRadius;
}

Asteroid::~Asteroid(void)
{
}

void Asteroid::render(bool haptics)
{
	glShadeModel(GL_SMOOTH);
	glColor3f(0.7, 0.4, 0.0);

	if (haptics)
	{
		mesh.renderHaptics(position, radius, hapticId);
	}
	else
	{
		mesh.render(position, radius);
	}
}
