#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <math.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/freeglut.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/gl.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/glu.h>

#define WIDTH 600
#define DEPTH 600
#define HALF_WIDTH WIDTH / 2
#define HALF_DEPTH DEPTH / 2

class Stage
{
public:
	Stage();
	static void display();

private:
	static void floor();
	static void draw();
};
