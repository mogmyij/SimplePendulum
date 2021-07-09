#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include <cmath>
#include "PendulumModel.h"
#include "macros.h"

PendulumModel::PendulumModel() {
	//init the vao and vbo of line (only the attributes. Data is filled in later)
	GLCall(glGenVertexArrays(1, &line.vao));
	GLCall(glBindVertexArray(line.vao));
	GLCall(glGenBuffers(1, &line.vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, line.vbo));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	GLCall(glEnableVertexAttribArray(0));
	//create the unit vector of the line which will be transformed to create multiple different pendulums
	//the length of the unit vector is 1 so that it is easy to manipulate (just multiply by the desired length)
	float lineArray[4]{ 0.0,0.0,1.0,0.0 };
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, &lineArray, GL_STATIC_DRAW));

	//init the vao and vbo of ball (only the attributes. Data is filled in later)
	GLCall(glGenVertexArrays(1, &ball.vao));
	GLCall(glBindVertexArray(ball.vao));
	GLCall(glGenBuffers(1, &ball.vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ball.vbo));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	GLCall(glEnableVertexAttribArray(0));
	//generate the circle around the point 0,0 this circle can then be translated to any other position
	float ballArray[(NUMBER_OF_TRIANGLES_IN_CIRCLE + 2) * 2]{ 0,0 };
	float tempTheta = 0;
	int count = 0;
	float x = 0; // the x displacement from origin
	float y = 0; // the y displacement from origin
	//find the increment of theta for each triangle
	float beta = (2 * M_PI) / NUMBER_OF_TRIANGLES_IN_CIRCLE;
	//loop through to fill up array with vertex points
	while (count <= NUMBER_OF_TRIANGLES_IN_CIRCLE)
	{
		ballArray[count * 2 + 2] = (RADIUS_OF_BALL) * (sin(tempTheta));//x values
		ballArray[count * 2 + 3] = (RADIUS_OF_BALL) * (cos(tempTheta));//y values
		tempTheta += beta;
		count++;
	}
	// fill buffer with circle centered around 0,0
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ((NUMBER_OF_TRIANGLES_IN_CIRCLE + 2) * 2), &ballArray, GL_STATIC_DRAW));

	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

//update the pendulum object's attribute based on the time period given
void PendulumModel::updatePendulumObjects(float time, float g) {

}

//draw the pendulum
void PendulumModel::draw() {
	//draw the line
	GLCall(glBindVertexArray(line.vao));
	GLCall(glDrawArrays(GL_LINES, 0, 2));

	//draw the ball
	GLCall(glBindVertexArray(ball.vao));
	GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, (NUMBER_OF_TRIANGLES_IN_CIRCLE + 2)));
}


PendulumModel::~PendulumModel() {
	//delete VAO and VBO
}
