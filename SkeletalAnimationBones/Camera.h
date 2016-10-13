#pragma once

#include <glm/gtc/matrix_transform.inl> 
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/freeglut_std.h> 

class Camera
{
public:
	static float moveSpeed;
	static float mouseSensitivity;
	Camera();
	void keyOperations();
	void apply();
	static void mouseMove(int x, int y);
	static void mouseScroll(int button, int dir, int x, int y);
	static void keyPressed(unsigned char key, int x, int y);
	static void keyUp(unsigned char key, int x, int y);
	static void specialKeyPressed(int key, int x, int y);
	static void specialKeyUp(int key, int x, int y);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void moveUp();
	void moveDown();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	static void rotateY(int dir);
	static void rotateX(int dir);
	static void rotatez(int dir);
	void setSpeed(float speed) const;
	void addToX(float x);
	void addToY(float y);
	void addToZ(float z);
	static float getRy();
	glm::vec3 getPosition() const;

private:
	glm::vec3 pos;
	glm::mat4 projView;
	glm::mat4 prodMatrix;
	glm::mat4 proj;
	glm::vec3 upVec = {0, 1, 0};
	glm::vec3 zeroVec = {0, 0,0};
	bool wireframe = true;
	static float fov;
	static int windowWidth;
	static int windowHeight;
	static bool mouseLock;
	static float rx;
	static float ry;
	static float rz;
	static float verticalAngle;
	static float horizontalAngle;
	static float initialFoV;
	glm::vec3 direction() const;
	glm::vec3 right() const;
};
