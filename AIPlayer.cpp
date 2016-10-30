#include "AIPlayer.h"

void AIPlayer::ChaseTheBall(Ball *myBall, Pad *myPad, PadController  *myController, float deltaTime, float padSpeed)
{
	// Need to check the position Y between ball and my pad, then move it towards the ball.

	if ((myBall->GetPosY() + myBall->GetRadius()) < (myPad->GetY() + myPad->GetHeight() / 2))
	{
		myController->MovePad(0, -deltaTime * padSpeed, 1);
	}
	else if((myBall->GetPosY() + myBall->GetRadius()) > (myPad->GetY() + myPad->GetHeight() / 2))
	{
		myController->MovePad(0, deltaTime * padSpeed, 1);
	}

	return;
}

AIPlayer::AIPlayer()
{
}


AIPlayer::~AIPlayer()
{
}
