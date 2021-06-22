#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>

#include "pendulum.h"
#include "macros.h"

static unsigned int compileShader(unsigned int type, std::string shaderSource) {
	GLCall(unsigned int shader = glCreateShader(type));
	const char* source = &shaderSource[0];
	GLCall(glShaderSource(shader, 1, &source, NULL));
	GLCall(glCompileShader(shader));

	int compileStatus;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus == GL_FALSE)
	{
		int len;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len));
		char* errorLog = (char *)alloca((len) * sizeof(char));
		GLCall(glGetShaderInfoLog(shader, len * sizeof(char), &len, errorLog));

		std::cout << "fail to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment: ") << std::endl;
		std::cout << errorLog << std::endl;

		GLCall(glDeleteShader(shader));
		return 0;
	}

	return shader;
}

static unsigned int createShader(std::string vertexSource, std::string fragmentSource) {
	GLCall(unsigned int program = glCreateProgram());

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	if ((vertexShader || fragmentShader) == 0)
	{
		GLCall(glDeleteProgram(program));
		return 0;
	}

	GLCall(glAttachShader(program, vertexShader));
	GLCall(glAttachShader(program, fragmentShader));
	GLCall(glLinkProgram(program));

	GLCall(glValidateProgram(program));
	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));
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

	Pendulum test = Pendulum(DEG_TO_RAD(20.0f), CENTIMETER(50.0f), 0.0, 0.0);

	//use shader
	std::string vertexSource;
	std::string fragmentSource;

	readSourceFile("../res/VertexShader.shader", &vertexSource);
	readSourceFile("../res/FragmentShader.Shader", &fragmentSource);

	unsigned int shader = createShader(vertexSource, fragmentSource);
	GLCall(glUseProgram(shader));



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		test.draw();
		/* Swap front and back buffers */

		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}