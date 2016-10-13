#include "Camera.h" 

float Camera::moveSpeed = 0.2;

static bool* keyStates = new bool[256];
static bool* keySpecialStates = new bool[246];

float Camera::initialFoV = 70.0f;
float Camera::fov = initialFoV;

Camera::Camera()
{
	pos = { 0, 0.5, 5 };
}

void Camera::apply(float move, aiVector3D objectPosition)
{
	keyOperations();

	gluLookAt(pos[0], pos[1], pos[2], objectPosition[0] * move, objectPosition[1] * move, objectPosition[2] * move, upVec[0], upVec[1], upVec[2]);
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
