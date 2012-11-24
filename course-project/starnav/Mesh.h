#pragma once

#include <string>
#include <vector>

#include "Vector.h"

struct Point
{
	double x, y, z;
};
struct Triangle
{
	std::vector<Point> points;
};

class Mesh
{
public:
	Mesh(const double* points);
	virtual ~Mesh(void);

	void render(Vector position, double radius);
	void renderHaptics(Vector position, double radius, unsigned int hapticId);

private:
	int displayListId;
};
