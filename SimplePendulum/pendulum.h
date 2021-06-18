#pragma once

//object is used to render the ball and line on the screen as well as track the theta value of the pendulum
class Pendulum {
private:
	float theta;
	float radius;
	float angularVelocity;
	float originX;
	float originY;
	struct pendulumLine
	{
		unsigned int vao;
	};
	pendulumLine line;
	struct pendulumBall
	{
		unsigned int vao;
	};
	pendulumBall ball;

public:
	Pendulum(float t,float r,float ox,float oy);
	void update(float time, float g);
	void draw();
	int updateGL();
	float getTheta();
	float getRadius();
	float getAngularVelocity();
	~Pendulum();

};