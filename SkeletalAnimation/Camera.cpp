#include "Camera.h" 
#include <iostream>

float Camera::moveSpeed = 1;

static bool* keyStates = new bool[256];
static bool* keySpecialStates = new bool[246];

Camera::Camera()
{
	viewAngle = 90;
	pos = {0, 0.5, 5};
}

void Camera::apply(float move, aiVector3D objectPosition)
{
	keyOperations();
	auto x = 3 * cosf(float(viewAngle) * CDR);
	auto z = 3 * sinf(float(viewAngle) * CDR);
	gluLookAt(x, pos.y, z, objectPosition[0] * move, objectPosition[1] * move, objectPosition[2] * move, upVec.x, upVec.y, upVec.z);
}

void Camera::keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;
}

void Camera::keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

void Camera::specialKeyPressed(int key, int x, int y)
{
	keySpecialStates[key] = true;
}

void Camera::specialKeyUp(int key, int x, int y)
{
	keySpecialStates[key] = false;
}

void Camera::keyOperations(void)
{
	if (keySpecialStates[GLUT_KEY_LEFT])
	{
		updateAngle(-moveSpeed);
	}
	if (keySpecialStates[GLUT_KEY_RIGHT])
	{
		updateAngle(moveSpeed);
	}
}

void Camera::updateAngle(float change)
{
	viewAngle += change;
	if (viewAngle < 0) viewAngle = 359;
	if (viewAngle >= 360) viewAngle = 0;
}

void Camera::setX(float x)
{
	pos.x = x;
}

void Camera::setY(float y)
{
	pos.y = y;
}

void Camera::setZ(float z)
{
	pos.z = z;
}

void Camera::setSpeed(float speed) const
{
	this->moveSpeed = speed;
}

void Camera::addToX(float x)
{
	pos.x += x;
}

void Camera::addToY(float y)
{
	pos.y += y;
}

void Camera::addToZ(float z)
{
	pos.z += z;
}

glm::vec3 Camera::getPosition() const
{
	return pos;
}
