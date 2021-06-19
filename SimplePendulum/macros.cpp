#include "macros.h"
#include <iostream>

void GLClearErrors() {
	while (glGetError()!= GL_NO_ERROR);
}

bool GLLogErrors() {
	bool haveError = false;
	GLenum error= glGetError();
	while (error != GL_NO_ERROR)
	{
		std::cout << error << std::endl;
		haveError = true;
	}
	return haveError;
}