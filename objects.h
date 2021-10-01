#ifndef OBJS_H
#define OBJS_H

// DEPENDENCIES
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Supress depreciated warnings
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif

#ifndef RES
#define RES 1
#endif


// Objects
void cube(
	double px, double py,double pz, // Position
	double sx,double sy,double sz, // Scale
	double rx, double ry, double rz, // Rotation
	GLubyte color[]  // Color
);

void arc(
	double px, double py,double pz, // Position
	double sx,double sy,double sz, // Scale
	double bx, double by, double bz, // Cube Size
	GLubyte color[], double a, double width, int pieces  // Color, angle, width, pieces
);

#endif