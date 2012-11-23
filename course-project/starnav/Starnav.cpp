#define WIN32
#include <HL/hl.h>

#include "Starnav.h"

Starnav::Starnav(void)
{
	ship = new Ship();
	allObjects.push_back(ship);

	allObjects.push_back(new Asteroid(Vector(-5, 3, -2), 1));
	allObjects.push_back(new Asteroid(Vector(5, 6, -1), 1));
	allObjects.push_back(new Asteroid(Vector(3, -5, -1), 1));
}

Starnav::~Starnav(void)
{
}

void Starnav::simulate()
{
	for (unsigned int i = 0; i < allObjects.size(); i++)
	{
		allObjects[i]->simulate(allObjects);
	}	
}

void Starnav::renderAll()
{
	render(false);
}

void Starnav::renderAllHaptics()
{
	render(true);
}

void Starnav::render(bool haptics)
{
	for (unsigned int i = 0; i < allObjects.size(); i++)
	{
		allObjects[i]->render(haptics);
	}	
}
