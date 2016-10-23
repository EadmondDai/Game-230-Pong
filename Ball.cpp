#include "Ball.h"

int Ball::SetDirection(float x, float y)
{
	X = x;
	Y = y;
	return 0;
}

int Ball::SetSpeed(float speed)
{
	Speed = speed;
	return 0;
}

int Ball::AddSpeed(float speed)
{
	Speed += speed;
	return 0;
}

int Ball::Move()
{
	float directionSum = X + Y;
	X = Speed / directionSum * X;
	Y = Speed / directionSum * Y;

	BallShape.setPosition(X, Y);

	return 0;
}

Ball::Ball()
{
	BallShape.setRadius(Radius);
}


Ball::~Ball()
{
}
