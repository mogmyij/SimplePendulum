#pragma once
#include <list>

//object is used to render the ball and line on the screen as well as track the theta value of the pendulum
class PendulumModel {
private:

	struct pendulumLine
	{
		unsigned int vao;
		unsigned int vbo;
	};
	pendulumLine line;

	struct pendulumBall
	{
		unsigned int vao;
		unsigned int vbo;
	};
	pendulumBall ball;

	struct pendulumObject 
	{
		float theta;
		float length;
		float angularVelocity;
		float originX;
		float originY;
	};
	std::list<pendulumObject> pendulumObjectlist;

public:
	PendulumModel();
	void updatePendulumObjects(float time, float g);
	int addPendulumObject(float theta,float radius,float originX,float originY);
	void genTransformationMatrix();
	void draw();
	pendulumObject getPendulumObject(int index);
	~PendulumModel();

};