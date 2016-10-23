#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class Pad
{
private:
	float X;
	float Y;
	float Width;
	float Height;

	// 0 means BlueTeam, 1 means RedTeam
	int TeamFLag;

	RectangleShape PadShape;

public:

	float GetX() { return X; };
	float GetY() { return Y; };
	float GetWidth() { return Width; };
	float GetHeight() { return Height; };
	void SetTeamFlag(int TeamFlag);
	void SetPosition(float x, float y);
	void SetSize(float width, float height);

	RectangleShape GetShape() { return PadShape; };

	void Move(float x, float y);

	Pad();
	~Pad();
};

