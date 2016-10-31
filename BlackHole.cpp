#include "BlackHole.h"

void BlackHole::SetPos(float x, float y)
{
	X = x; 
	Y = y;

	Hole.setPosition(X, Y);
};

BlackHole::BlackHole()
{
	Hole.setFillColor(Color::Black);
	Hole.setOrigin(ShapRadius, ShapRadius);
	Hole.setRadius(ShapRadius);
}


BlackHole::~BlackHole()
{
}
