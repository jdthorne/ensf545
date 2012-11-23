#pragma once

#include <vector>

#include "Ship.h"
#include "Asteroid.h"
#include "Vector.h"

class Starnav
{
public:
	Starnav(void);
	~Starnav(void);

	void simulate();

	void renderAll();
	void renderAllHaptics();

private:
	void render(bool haptics);

private:
	Ship* ship;

	std::vector<Physics*> allObjects;
};
