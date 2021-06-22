#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include <cmath>
#include "pendulum.h"
#include "macros.h"
#include <chrono>

//update the vbo with the correct vertex data
void Pendulum::updateGL() {
	//calculate the coordinates of the end of the line
	//find end of the line based on the radius and theta
	float endOfLineX = originX + (cos(theta)*radius);
	float endOfLineY = originY + (sin(theta)*radius);

	//init line and ball array
	//number of triangles in circle + 4 because 2 extra vertex need to be stored
	//:the center of the circle and a duplicate of the first triangle vertex
	float lineArray[4]{ originX,originY ,endOfLineX,endOfLineY };
	float ballArray[(NUMBER_OF_TRIANGLES_IN_CIRCLE + 2) * 2]{ endOfLineX,endOfLineY };

	//update line vertex data
	GLCall(glBindVertexArray(line.vao));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, line.vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, &lineArray, GL_DYNAMIC_DRAW));

	//update ball vertex data
	// the origin of the ball is the end of the line 
	GLCall(glBindVertexArray(ball.vao));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ball.vbo));
	float tempTheta = 0;
	int count = 0;
	float x = 0; // the x displacement from origin
	float y = 0; // the y displacement from origin
	//find the increment of theta for each triangle
	float beta = (2 * M_PI) / NUMBER_OF_TRIANGLES_IN_CIRCLE;

	//loop through to fill up array with vertex points
	while (count <= NUMBER_OF_TRIANGLES_IN_CIRCLE)
	{
		x = (RADIUS_OF_BALL) * (sin(tempTheta));
		y = (RADIUS_OF_BALL) * (cos(tempTheta));
		ballArray[count * 2 + 2] = endOfLineX + x;
		ballArray[count * 2 + 3] = endOfLineY + y;
		tempTheta += beta;
		count++;
	}
	//fill up vertex buffer with array
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ((NUMBER_OF_TRIANGLES_IN_CIRCLE + 2) * 2), &ballArray, GL_DYNAMIC_DRAW));

	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

Pendulum::Pendulum(float t, float r, float ox, float oy) {
	//add 270 degrees to the specified theta because the resting point of a pendulum is verticaly downwards.
	//therefore addition of 270 is needed for correct vector calculations
	theta = t + (1.5*M_PI);
	radius = r;
	originX = ox;
	originY = oy;
	//init the vao and vbo of line (only the attributes. Data is filled in later)
	GLCall(glGenVertexArrays(1, &line.vao));
	GLCall(glBindVertexArray(line.vao));
	GLCall(glGenBuffers(1, &line.vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, line.vbo));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	GLCall(glEnableVertexAttribArray(0));
	//init the vao and vbo of ball (only the attributes. Data is filled in later)
	GLCall(glGenVertexArrays(1, &ball.vao));
	GLCall(glBindVertexArray(ball.vao));
	GLCall(glGenBuffers(1, &ball.vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ball.vbo));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	GLCall(glEnableVertexAttribArray(0));
	updateGL();
	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

//update the pendulum object's attribute based on the time period given
void Pendulum::updatePendulum(float time, float g) {

}

//draw the pendulum
void Pendulum::draw() {
	//draw the line
	GLCall(glBindVertexArray(line.vao));
	GLCall(glDrawArrays(GL_LINES, 0, 2));

	//draw the ball
	GLCall(glBindVertexArray(ball.vao));
	GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, (NUMBER_OF_TRIANGLES_IN_CIRCLE + 2)));
}

float Pendulum::getTheta() {
	return 0;
}
float Pendulum::getRadius() {
	return 0;
}
float Pendulum::getAngularVelocity() {
	return 0;
}

Pendulum::~Pendulum() {
	//delete VAO and VBO
}
