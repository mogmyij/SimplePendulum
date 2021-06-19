#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include "pendulum.h"
#include "macros.h"

static unsigned int compileShader(unsigned int type, std::string shaderSource) {
	unsigned int shader = glCreateShader(type);
	const char* source = &shaderSource[0];
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		int len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		char* errorLog = (char *)alloca((len) * sizeof(char));
		glGetShaderInfoLog(shader, len * sizeof(char), &len, errorLog);

		std::cout << "fail to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment: ") << std::endl;
		std::cout << errorLog << std::endl;

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

static unsigned int createShader(std::string vertexSource, std::string fragmentSource) {
	unsigned int program = glCreateProgram();

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	if ((vertexShader || fragmentShader) == 0)
	{
		glDeleteProgram(program);
		return 0;
	}

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glValidateProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}

static void readSourceFile(std::string filePath, std::string * source) {
	std::ifstream file;
	file.open(filePath, std::fstream::in);
	std::string line;
	std::string shaderSource;

	std::stringstream ss;
	while (!file.eof())
	{
		std::getline(file, line);
		ss << line;
		ss << std::endl;
	}
	shaderSource = ss.str();
	*source = shaderSource;
	return;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//use the core profile of openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	unsigned int err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "GLEW Init error" << std::endl;
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}