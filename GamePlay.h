#pragma once
#include "PadController.h"
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PadController.h"
#include "Ball.h"

using namespace sf;

// This class will handle all the gamelogic. Check if winning.
// This class will also handle all the rendering staff.

class GamePlay
{
private:
	// 0 means in game, 1 means scoring, 2 means winning.
	int GameState = 0;

	float ScoreTime;

	float ScoreEndTime;

	float PadSpeed = 500000;

	PadController MyController;

	Ball Ball;

public:
	// Hanlde ball move and pad move.
	int PlayGame();
	
	// Handle score check.
	int Score();
	
	// Handle winning congratulation.
	int Winning();

	int GetGameState() { return GameState; };

	PadController GetPadController() { return MyController; };

	GamePlay();
	~GamePlay();
};

