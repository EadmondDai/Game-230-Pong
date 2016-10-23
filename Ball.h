#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

// The ball is always moving. 
class Ball
{
private:
	float Speed = 1;
	float X = 1;
	float Y = 1;
	float Radius = 10;

	float DirectionX;
	float DirectionY;
	
	CircleShape BallShape;

public:
	int SetDirection(float x, float y);
	int AddSpeed(float speed);
	int SetSpeed(float speed);
	Vector2f GetDirection() { return Vector2f(X, Y); };
	CircleShape GetBallShape() { return BallShape; };
	int Move();

	Ball();
	~Ball();
};

