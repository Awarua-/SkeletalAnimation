#include "Box.h"

Box::Box()
{
}

void Box::display()
{
	glPushMatrix();
	glTranslatef(0, 2, 0);
	draw();
	glPopMatrix();
}

void Box::draw()
{
	glBegin(GL_QUADS);
	glutSolidCube(10);
	glEnd();
}
