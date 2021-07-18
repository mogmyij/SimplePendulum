#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include <cmath>
#include "PendulumModel.h"
#include "macros.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


PendulumModel::PendulumModel() {
	numberOfPendulumObjects = 0;
	//init the vao and vbo of line (only the attributes. Data is filled in later)
	GLCall(glGenVertexArrays(1, &line.vao));
	GLCall(glBindVertexArray(line.vao));
	GLCall(glGenBuffers(1, &line.vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, line.vbo));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	GLCall(glEnableVertexAttribArray(0));
	//create the unit vector of the line which will be transformed to create multiple different pendulums
	//the length of the unit vector is 1 so that it is easy to manipulate (just multiply by the desired length)
	float lineArray[4]{ 0.0,0.0,0.0,-1.0 };
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, &lineArray, GL_STATIC_DRAW));
	//init the instanced array
	GLCall(glGenBuffers(1, &line.vboInstanced));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, line.vboInstanced));
	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, 0));
	GLCall(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(sizeof(float) * 4)));
	GLCall(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(sizeof(float) * 8)));
	GLCall(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(sizeof(float) * 12)));
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glEnableVertexAttribArray(3));
	GLCall(glEnableVertexAttribArray(4));


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

	//init the instanced array
	GLCall(glGenBuffers(1, &ball.vboInstanced));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ball.vboInstanced));
	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, 0));
	GLCall(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(sizeof(float) * 4)));
	GLCall(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(sizeof(float) * 8)));
	GLCall(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(sizeof(float) * 12)));
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glEnableVertexAttribArray(3));
	GLCall(glEnableVertexAttribArray(4));

	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

int PendulumModel::getNumberOfPendulumObjects() {
	return numberOfPendulumObjects;
}

void PendulumModel::addPendulumObject(float theta, float length, float originX, float originY) {
	//initialize new pendulum object
	pendulumObject newPendulum{ theta,length,originX,originY,0.0 };
	// add newpendulum object to list
	pendulumObjectList.push_back(newPendulum);
	numberOfPendulumObjects++;
};

//update the pendulum object's physics
void PendulumModel::updatePendulumObjects(double deltaTime, float g) {
	//loop through each pendulum object to perform numerical integration
	std::list<pendulumObject>::iterator pendulumIterator = pendulumObjectList.begin();
	pendulumObject po;
	float instantaneousAngularAcceleration;
	while (pendulumIterator != pendulumObjectList.end())
	{
		//perform semi-implicit euler calculate velocity using acceleration before changing position
		po = *pendulumIterator;

		po.angularVelocity += ((-(g / po.length))*sin(po.theta)*deltaTime);
		po.theta += po.angularVelocity*deltaTime;

		pendulumIterator = pendulumObjectList.erase(pendulumIterator);
		pendulumIterator = pendulumObjectList.insert(pendulumIterator, po);

		pendulumIterator++;
	}
}

void PendulumModel::genTransformationMatrix() {
	glm::mat4 lineTransform = glm::mat4(1.0f);
	glm::mat4 circleTransform = glm::mat4(1.0f);
	float *lineInstancedArray = new float[numberOfPendulumObjects * 16];
	float *circleInstancedArray = new float[numberOfPendulumObjects * 16];
	float *matPointer;
	std::list<pendulumObject>::iterator pendulumIterator = pendulumObjectList.begin();
	pendulumObject po;

	float circleX;
	float circleY;
	float trigoTheta;//converts the theta in our pendulum object to a easier to use value in trigonometry
	int index = 0;
	while (index < numberOfPendulumObjects)
	{
		po = *pendulumIterator;
		//order of matrix multiplication translate*rotate*scale
		//line transformation (move position to origin)
		lineTransform = glm::translate(lineTransform, glm::vec3(po.originX, po.originY, 0.0f));
		//line rotate
		lineTransform = glm::rotate(lineTransform, (po.theta), glm::vec3(0.0f, 0.0f, 1.0f));
		//line scale
		lineTransform = glm::scale(lineTransform, glm::vec3(METER(po.length), METER(po.length), METER(po.length)));

		//circle transformation ( translate position)
		trigoTheta = po.theta + (1.5*M_PI);
		circleX = po.originX + (METER(po.length) * cos(trigoTheta));
		circleY = po.originY + (METER(po.length) * sin(trigoTheta));
		circleTransform = glm::translate(circleTransform, glm::vec3(circleX, circleY, 0.0f));

		//add the matrixes to the instanced arrays
		//line
		matPointer = glm::value_ptr(lineTransform);
		for (int i = 0; i < 16; i++)
		{
			lineInstancedArray[(index * 16) + i] = matPointer[i];
		}
		//circle
		matPointer = glm::value_ptr(circleTransform);
		for (int i = 0; i < 16; i++)
		{
			circleInstancedArray[(index * 16) + i] = matPointer[i];
		}
		index++;
		lineTransform = glm::mat4(1.0f);
		circleTransform = glm::mat4(1.0f);
		pendulumIterator++;
	}

	//update the line instanced VBO
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, line.vboInstanced));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (numberOfPendulumObjects * 16), lineInstancedArray, GL_DYNAMIC_DRAW));
	delete lineInstancedArray;

	//update the circle instanced VBO
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ball.vboInstanced));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (numberOfPendulumObjects * 16), circleInstancedArray, GL_DYNAMIC_DRAW));
	delete circleInstancedArray;

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

//draw the pendulum
void PendulumModel::draw() {
	//draw the line
	GLCall(glBindVertexArray(line.vao));
	GLCall(glDrawArraysInstanced(GL_LINES, 0, 2, numberOfPendulumObjects));

	//draw the ball
	GLCall(glBindVertexArray(ball.vao));
	GLCall(glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, (NUMBER_OF_TRIANGLES_IN_CIRCLE + 2), numberOfPendulumObjects));
}


PendulumModel::~PendulumModel() {
	//delete VAO and VBO
}
