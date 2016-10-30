#include "Ball.h"

int Ball::SetDirection(float x, float y)
{
	DirectionX = x;
	DirectionY = y;
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
	float directionSum = fabs(DirectionX) + fabs(DirectionY);
	X += Speed / directionSum * DirectionX;
	Y += Speed / directionSum * DirectionY;

	BallShape.setPosition(X, Y);

	return 0;
}

void Ball::InitPos()
{
	X = 400 - Radius;
	Y = 300 - Radius;

	Speed = 0.1;

	// Keep current X direction.
	DirectionY = 0;

	if (DirectionX > 0)
	{
		DirectionX = 1;
	}
	else
	{
		DirectionX = -1;
	}

}

Ball::Ball()
{
	BallShape.setRadius(Radius);
	InitPos();
}


Ball::~Ball()
{
}
