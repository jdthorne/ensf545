#define WIN32
#include <HL/hl.h>
#include <GL/glut.h>

#include "Starnav.h"
#include <cstdlib>
#include <cmath>

#include <iostream>
#include <fstream>

using namespace std;
static char background[1024 * 768 * 4];

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Starnav::Starnav(void)
{
	ship = new Ship();
	allObjects.push_back(ship);

	int asteroidsToAdd = 50;
	while (asteroidsToAdd > 0)
	{
		Vector position = Vector(fRand(-3, 3), fRand(-3, 3), fRand(-6, 6));
		double radius = pow(fRand(0.3, 1.0), 2);

		Asteroid* asteroid = new Asteroid(position, radius);
		if (asteroid->collidesWithAny(allObjects))
		{
			delete asteroid;
			continue;
		}

		allObjects.push_back(asteroid);
		asteroidsToAdd--;
	}

	ifstream image("../../../image/image.raw", ios::binary);
	image.read(background, 1024*768*4);
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
	for (unsigned int i = 0; i < allObjects.size(); i++)
	{
		allObjects[i]->simulateHaptics();
	}	
}

void Starnav::render(bool haptics)
{
	for (unsigned int i = 0; i < allObjects.size(); i++)
	{
		allObjects[i]->render(haptics);
	}	
}
