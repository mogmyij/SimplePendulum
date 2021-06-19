#pragma once

#include <GL/glew.h>

#define ASSERT(x) if ((x)) __debugbreak();
#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GLLogErrors());

void GLClearErrors();
bool GLLogErrors();