#include "Stage.h"

Stage::Stage()
{
}

void Stage::draw()
{
	floor();
}

void Stage::display()
{
	glPushMatrix();
	draw();
	glPopMatrix();
}

//-- Ground Plane --------------------------------------------------------
void Stage::floor()
{
	glDisable(GL_LIGHTING);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-500, 0, -500);
	glNormal3f(0, 1, 0);
	glVertex3f(-500, 0, 500);
	glNormal3f(0, 1, 0);
	glVertex3f(500, 0, 500);
	glNormal3f(0, 1, 0);
	glVertex3f(500, 0, -500);
	glEnd();
	glEnable(GL_LIGHTING);
}
