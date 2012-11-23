#pragma once

#include "Vector.h"
#include "Mesh.h"
#include "Physics.h"

class Asteroid : public Physics
{
public:
	Asteroid(Vector position, double radius);
	~Asteroid(void);

	void render(bool haptics);

private:
	Mesh mesh;
};
