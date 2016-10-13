#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <math.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/freeglut.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/gl.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <GL/glu.h>

class Box
{
public:
	Box();
	static void display();

private:
	static void draw();
};