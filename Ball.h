#pragma once
#include <Math.h>

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

// The ball is always moving. 
class Ball
{
private:
	// Use to relocate the ball.
	bool IfSpawnTop = true;

	float Speed = 5;

	// The position is the topleft corner of the shape.
	float X;
	float Y;
	float Radius = 10;

	// Direction can not be zero. At least can not both be zero.
	// The abs value of direction sum should always be 1.
	float DirectionX = 1;
	float DirectionY = 0;
	
	CircleShape BallShape;

public:
	int SetDirection(float x, float y);
	int AddSpeed(float speed);
	int SetSpeed(float speed);

	float GetSpeed() { return Speed; }
	float GetPosX() { return X; }
	float GetPosY() { return Y; }
	float GetRadius() { return Radius; }
	
	void InitPos();
	void MoveWithAPos(float x, float y);

	Vector2f GetDirection() { return Vector2f(DirectionX, DirectionY); }
	CircleShape GetBallShape() { return BallShape; }
	int Move();

	Ball();
	~Ball();
};

