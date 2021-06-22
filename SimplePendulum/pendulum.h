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
		unsigned int vbo;
	};
	pendulumLine line;

	struct pendulumBall
	{
		unsigned int vao;
		unsigned int vbo;
	};
	pendulumBall ball;

public:
	Pendulum(float t,float r,float ox,float oy);
	void updatePendulum(float time, float g);
	void draw();
	void updateGL();
	float getTheta();
	float getRadius();
	float getAngularVelocity();
	~Pendulum();

};