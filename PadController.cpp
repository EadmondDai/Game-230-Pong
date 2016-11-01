#include "PadController.h"

int PadController::MovePad(float x, float y, int teamFlag)
{
	if (teamFlag == 0)
	{
		float yOffset = GetYOffset(BluePad.GetY(), y);
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
	else if (y + moveY + PadHeight > 600)
	{
		return 600 - y - moveY - PadHeight;
	}
	else
	{
		return moveY;
	}
}

void PadController::InitPadsPos()
{
	BluePad.SetPosition(10, 280);
	RedPad.SetPosition(780, 280);
}

PadController::PadController()
{
	InitPadsPos();

	BluePad.SetSize(10, 70);
	BluePad.SetTeamFlag(0);
	RectangleShape blueShape = BluePad.GetShape();

	RedPad.SetSize(10, 70);
	RedPad.SetTeamFlag(1);
	RectangleShape redShape = RedPad.GetShape();

	PadHeight = BluePad.GetHeight();
}

PadController::~PadController()
{
}
