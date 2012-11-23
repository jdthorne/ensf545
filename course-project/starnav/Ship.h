#pragma once

#include "Physics.h"
#include "Mesh.h"

class Ship : public Physics
{
public:
	Ship(void);
	~Ship(void);
	
	void render(bool haptics);

private:
	Mesh mesh;
};
