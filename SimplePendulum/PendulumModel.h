#pragma once
#include <list>
#include "macros.h"

//object is used to render the ball and line on the screen as well as track the theta value of the pendulum
class PendulumModel {
private:

	int numberOfPendulumObjects;

	struct pendulumLine
	{
		unsigned int vao;
		unsigned int vbo;
		unsigned int vboInstanced;
	};
	pendulumLine line;

	struct pendulumBall
	{
		unsigned int vao;
		unsigned int vbo;
		unsigned int vboInstanced;
	};
	pendulumBall ball;

	struct pendulumObject
	{
		float theta;
		float length;
		float originX;
		float originY;
		float angularVelocity;
	};
	std::list<pendulumObject> pendulumObjectList;

public:
	PendulumModel();
	void updatePendulumObjects(double deltaTime, float g);
	void addPendulumObject(float theta,float length,float originX,float originY);
	void genTransformationMatrix();
	void draw();
	int getNumberOfPendulumObjects();
	pendulumObject getPendulumObject(int index);
	~PendulumModel();

};