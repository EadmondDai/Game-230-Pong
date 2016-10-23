#include "PadController.h"

int PadController::MovePad(float x, float y, int teamFlag)
{
	if (teamFlag == 0)
	{
		float yOffset = GetYOffset(BluePad.GetY(), y);
		printf("y %f  yOffset %f", y, yOffset);
		BluePad.Move(x, yOffset);
	}
	else
	{
		float yOffset = GetYOffset(RedPad.GetY(), y);
		RedPad.Move(x, yOffset);
	}

	return 0;
}

float PadController::GetYOffset(float y, float moveY)
{
	if (y + moveY < 0)
	{
		return y - 0;
	}
	else if (y + moveY > 600)
	{
		return 600 - y;
	}
	else
	{
		return moveY;
	}
}

PadController::PadController()
{
	BluePad.SetPosition(10, 100);
	BluePad.SetSize(10, 70);
	BluePad.SetTeamFlag(0);
	RectangleShape blueShape = BluePad.GetShape();
	blueShape.setFillColor(Color(0, 0, 255));
	blueShape.setOutlineColor(Color::Cyan);

	RedPad.SetPosition(780, 100);
	RedPad.SetSize(10, 70);
	RedPad.SetTeamFlag(1);
	RectangleShape redShape = RedPad.GetShape();
	redShape.setFillColor(Color(255, 0, 0));
	redShape.setOutlineColor(Color::Magenta);

}



PadController::~PadController()
{
}
