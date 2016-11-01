#include "Ball.h"

int Ball::SetDirection(float x, float y)
{
	// Always normalise the direction.
	/*float temp = x * x + y * y;

	DirectionX = x * abs(x) / temp;
	DirectionY = y * abs(y) / temp;*/

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

void Ball::MoveWithAPos(float x, float y)
{
	X += x;
	Y += y;
}

void Ball::InitPos()
{
	X = 400 - Radius;
	Y = 200 - Radius;

	Speed = 5;

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
