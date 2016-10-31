#pragma once
#include <sfml/Graphics.hpp>

using namespace sf;

class BlackHole
{
private:
	float Range = 100;
	float Gravity = 10;
	float X = 0;
	float Y = 0;
	float ShapRadius = 20;

	CircleShape Hole;

public:

	float GetPosX() { return X; }
	float GetPosY() { return Y; }
	float GetRange() { return Range; }
	float GetGravity() { return Gravity; }
	float GetRadius() { return ShapRadius; }

	CircleShape GetMyShape() { return Hole; }

	void SetPos(float x, float y);

	void SetRange(float range) { Range = range; }

	void SetGravity(float gravity) { Gravity = gravity; }

	void SetRadius(float radius) { ShapRadius = radius; }

	BlackHole();
	~BlackHole();
};

