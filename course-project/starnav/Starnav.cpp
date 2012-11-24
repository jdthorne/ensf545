
#define WIN32
#include <HL/hl.h>
#include <GL/glut.h>

#include "Starnav.h"
#include "Ship.h"
#include "Asteroid.h"
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
	effectId = hlGenEffects(1);

	ship = new Ship();
	allObjects.push_back(ship);

	ifstream image("../../../image/image.raw", ios::binary);
	image.read(background, 1024*768*4);

#ifndef DIRECT_CONTROL
	generateAsteriods();
#endif
}

void Starnav::killAsteriods()
{
	allObjects.clear();
	allObjects.push_back(ship);
}
void Starnav::generateAsteriods()
{
	int asteroidsToAdd = 80;

#ifdef DIRECT_CONTROL
	asteroidsToAdd *= 2;
#endif

	while (asteroidsToAdd > 0)
	{
		Vector position = Vector(fRand(-6, 6), fRand(-6, 6), fRand(-6, 6));
		Vector drift = Vector(fRand(-1, 1), fRand(-1, 1), fRand(-1, 1));
		double radius = pow(fRand(0.6, 1.4), 2);

		Asteroid* asteroid = new Asteroid(position, drift, radius);
		if (asteroid->collidesWithAny(allObjects))
		{
			delete asteroid;
			continue;
		}

		allObjects.push_back(asteroid);
		asteroidsToAdd--;
	}
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

#ifdef DIRECT_CONTROL
	if (ship->exploded)
	{
		killAsteriods();
	}
	if (allObjects.size() == 1 && ship->position.z < -7)
	{
		ship->exploded = false;
		generateAsteriods();
	}
#else
	if (ship->exploded)
	{
		reset();
	}
#endif
}

void Starnav::reset()
{
	killAsteriods();
	generateAsteriods();

	ship->exploded = false;
	ship->position = Vector(0,0,-7);
	ship->velocity = Vector(0,0,0);
}

void Starnav::renderAll()
{
	render(false);
}

void Starnav::renderAllHaptics()
{

#ifndef DIRECT_CONTROL

	render(true);
	for (unsigned int i = 0; i < allObjects.size(); i++)
	{
		allObjects[i]->simulateHaptics();
	}	

	HLint buttons;
	hdGetIntegerv(HD_CURRENT_BUTTONS, &buttons);
	if (buttons == 1)
	{
		HLdouble pos[3];
		hlGetDoublev(HL_PROXY_POSITION, pos);
		Vector cursorPosition = Vector(pos[0], pos[1], pos[2]);

		Vector shipToCursor = (ship->position - cursorPosition).normalized();
		ship->velocity += shipToCursor * -0.001;
	}

#else

	// Haptic Touch
	HLdouble pos[3];
	hlGetDoublev(HL_PROXY_POSITION, pos);
	Vector cursorPosition = Vector(pos[0], pos[1], pos[2]);
	ship->push(cursorPosition);

	hlEffectd(HL_EFFECT_PROPERTY_MAGNITUDE, 50);
	hlEffectd(HL_EFFECT_PROPERTY_GAIN, 4);

	static bool started = false;
	if (!started)
	{
		hlStartEffect(HL_EFFECT_VISCOUS, effectId);
	}
	else
	{
		hlUpdateEffect(effectId);
	}
	started = true;

#endif

}

void Starnav::render(bool haptics)
{
	for (unsigned int i = 0; i < allObjects.size(); i++)
	{
		allObjects[i]->render(haptics);
	}	
}
