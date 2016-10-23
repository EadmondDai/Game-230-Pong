#include "Pad.h"

void Pad::Move(float x, float y)
{
	SetPosition(X + x, Y + y);
}

void Pad::SetPosition(float x, float y)
{
	X = x;
	Y = y;

	PadShape.setPosition(X, Y);

	
}

void Pad::SetSize(float width, float height)
{
	Width = width;
	Height = height;

	PadShape.setSize(Vector2f(width, height));
}

void Pad::SetTeamFlag(int teamFLag)
{
	TeamFLag = teamFLag;
}

Pad::Pad()
{
}


Pad::~Pad()
{
}
