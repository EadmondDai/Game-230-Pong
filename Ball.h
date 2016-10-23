#pragma once

// The ball is always moving. 
class Ball
{
private:
	float Speed;
	float X;
	float Y;
	float Radius;

	float DirectionX;
	float DirectionY;


public:
	int SetDirection(float x, float y);
	int AddSpeed(float x, float y);
	int Move();

	Ball();
	~Ball();
};

