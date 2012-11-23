#define WIN32
#include <HL/hl.h>

#include "Mesh.h"
#include "Helpers.h"

#include <fstream>
#include <iostream>
#include <GL/glut.h>


using namespace std;

Mesh::Mesh(const double points[])
{
	for (int face = 0; points[face*3] < 999; face++)
	{
		Triangle t;
		for (int point = 0; point < 3; point++)
		{
			Point p;
			p.x = points[(face*3) + point + 0];
			p.y = points[(face*3) + point + 1];
			p.z = points[(face*3) + point + 2];
			t.points.push_back(p);
		}
		faces.push_back(t);
	}
}

Mesh::~Mesh(void)
{
}

void Mesh::render(Vector position)
{
	glPushMatrix();
	glTranslatef(position.x(), position.y(), position.z());

	glutSolidSphere(1, 16, 16);
	//glScalef(0.2, 0.2, 0.2);

	/*glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < faces.size() / 3; i++)
	{
		for (unsigned int p = 0; p < 3; p++)
		{
			glVertex3f(faces[i].points[p].x, faces[i].points[p].y, faces[i].points[p].z);
		}
	}
	glEnd();*/


	glPopMatrix();
}

void Mesh::renderHaptics(Vector position, unsigned int hapticId)
{
	hlBeginShape(HL_SHAPE_FEEDBACK_BUFFER, hapticId);

	//render(position);

	hlEndShape();
}
