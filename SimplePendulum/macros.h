#pragma once
#include <GL/glew.h>

//convertion from meter/centimeter to gl units
#define METER(x) x/2
#define CENTIMETER(x) x/200

#define DEG_TO_RAD(x) x*(M_PI/180)
#define RAD_TO_DEG(x) x*(180/M_PI)

//settings for the ball
#define NUMBER_OF_TRIANGLES_IN_CIRCLE 300
#define RADIUS_OF_BALL CENTIMETER(3.0)

//error logging
#define ASSERT(x) if ((x)) __debugbreak();
#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GLLogErrors())

void GLClearErrors();
bool GLLogErrors();