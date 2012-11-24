#define WIN32
#include <HL/hl.h>

#include "Mesh.h"
#include "Helpers.h"

#include <fstream>
#include <iostream>
#include <GL/glut.h>


using namespace std;

Mesh::Mesh(const double* points)
{
	displayListId = glGenLists(1);
	glNewList(displayListId, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for (int i = 0; points[i] < 999; i += 6)
	{
		glNormal3f(points[i+0], points[i+1], points[i+2]);
		glVertex3f(points[i+3], points[i+4], points[i+5]);
	}
	glEnd();
	glEndList();
}

Mesh::~Mesh(void)
{
}

void Mesh::render(Vector position, double radius)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(radius, radius, radius);

	//glutSolidSphere(1, 16, 16);
	glCallList(displayListId);

	glPopMatrix();
}

void Mesh::renderHaptics(Vector position, double radius, unsigned int hapticId)
{
	hlBeginShape(HL_SHAPE_FEEDBACK_BUFFER, hapticId);

	render(position, radius);

	hlEndShape();
}
