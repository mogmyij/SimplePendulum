#define GLEW_STATIC
#define NUMBER_OF_TRIANGLES_IN_CIRCLE 300
#include <GL/glew.h>
#include <glfw3.h>
#include <cmath>
#include "pendulum.h"
#include "macros.h"


//update the vbo with the correct vertex data
int Pendulum::updateGL() {
	float lineArray[4]{ originX,originY };
	//number of triangles in circle + 4 because 2 extra vertex need to be stored, the center of the circle and a duplicate of the first triangle vertex
	float ballArray[NUMBER_OF_TRIANGLES_IN_CIRCLE+4];

	//update line vertex data
	GLCall(glBindVertexArray(line.vao));
	//find end of the line based on the radius and theta
	lineArray[2] = originX+(sin(theta)*radius);
	lineArray[3] = originY+(cos(theta)*radius);
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, &lineArray, GL_DYNAMIC_DRAW));
	
	//update ball vertex data
	GLCall(glBindVertexArray(ball.vao));
	return 0;
}

Pendulum::Pendulum(float t,float r,float ox,float oy) {
	theta = t;
	radius = r;
	originX = ox;
	originY = oy;
	//init the vao and vbo of line
	GLCall(glGenVertexArrays(1, &line.vao));
	GLCall(glBindVertexArray(line.vao));
	unsigned int lineVBO;
	GLCall(glGenBuffers(1, &lineVBO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER,lineVBO));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	//init the vao and vbo of ball
	GLCall(glGenVertexArrays(1, &ball.vao));
	GLCall(glBindVertexArray(ball.vao));
	unsigned int ballVBO;
	GLCall(glGenBuffers(1, &ballVBO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ballVBO));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	updateGL();
}

void Pendulum::update(float time, float g) {

}

void Pendulum::draw() {
	
}

float Pendulum::getTheta(){
	return 0;
}
float Pendulum::getRadius(){
	return 0;
}
float Pendulum::getAngularVelocity(){
	return 0;
}
Pendulum::~Pendulum(){
	
}
