#pragma once 

#include <glm/gtc/matrix_transform.inl> 
// ReSharper disable once CppUnusedIncludeDirective
#include <assimp/scene.h>
#include <assimp/types.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/freeglut.h>

class Camera
{
public:
	Camera();
	void apply(float move, aiVector3D objectPosition);
	void keyOperations();
	static void keyPressed(unsigned char key, int x, int y);
	static void keyUp(unsigned char key, int x, int y);
	static void specialKeyPressed(int key, int x, int y);
	static void specialKeyUp(int key, int x, int y);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setSpeed(float speed) const;
	void addToX(float x);
	void addToY(float y);
	void addToZ(float z);
	glm::vec3 getPosition() const;

private:
	glm::vec3 pos;
	glm::vec3 upVec = { 0, 1, 0 };
	glm::vec3 zeroVec = { 0, 0,0 };
	static float fov;
	static float moveSpeed;
	static float initialFoV;
};
