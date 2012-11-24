#pragma once

#include "Physics.h"
#include "Quaternion.h"
#include "Mesh.h"

class Ship : public Physics
{
public:
	Ship(void);
	~Ship(void);
	
	void render(bool haptics);
	virtual void handleCollision();

	void push(Vector direction);

public:
	bool exploded;

private:
	Quaternion orientation;
	Mesh mesh;
};
