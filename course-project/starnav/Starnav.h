#pragma once

//#define DIRECT_CONTROL

#include <vector>

#include "Vector.h"

class Ship;
class Physics;

class Starnav
{
public:
	Starnav(void);
	~Starnav(void);

	void simulate();

	void renderAll();
	void renderAllHaptics();

	void killAsteriods();
	void generateAsteriods();
	void reset();

private:
	void render(bool haptics);

private:
	int effectId;
	Ship* ship;

	std::vector<Physics*> allObjects;
};
