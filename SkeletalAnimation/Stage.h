#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <math.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/freeglut.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/gl.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/glu.h>

#define BACKGROUND_COLOUR 0.0, 0.0, 0.0, 0.0
#define PERSPECTIVE_PROJECTION 60., 1.0, 10.0, 1000.0
#define HALF_WIDTH 300
#define HALF_DEPTH 200

class Stage
{
public:
	Stage();
	void setAngle(int);
	void changeCameraViewAngle(int);
	static void display();

private:
	int cameraViewAngle;
	int cameraAngle;
	static void floor();
	static void draw();
	void drawCamera();
};
