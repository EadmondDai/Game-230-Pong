#pragma once
#include "PadController.h"
#include "Pad.h"
#include "Ball.h"

// This AI Player is responsiable to track the ball and counter.

class AIPlayer
{
private:


public:
	void ChaseTheBall(Ball *myBall, Pad *myPad, PadController *myController, float deltaTime, float padSpeed);

	AIPlayer();
	~AIPlayer();
};

