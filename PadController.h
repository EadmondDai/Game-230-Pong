#pragma once
#include "Pad.h"

class PadController
{
	Pad BluePad;
	Pad RedPad;

	float PadHeight;

	float GetYOffset(float y, float moveY);

public:

	Pad GetBluePad() { return BluePad; };
	Pad GetRedPad() { return RedPad; };
	RectangleShape GetBlueShape() { return BluePad.GetShape(); };
	RectangleShape GetRedShape() { return RedPad.GetShape(); };

	int MovePad(float x, float y, int teamFlag);

	PadController();
	~PadController();
};

