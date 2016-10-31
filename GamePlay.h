#pragma once
#include "PadController.h"
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "PadController.h"
#include "Ball.h"
#include "AIPlayer.h"
#include "SoundManager.h"
#include "BlackHole.h"

using namespace sf;
using std::to_string;

// This class will handle all the gamelogic. Check if winning.
// This class will also handle all the rendering staff.
// And this class will manage the score of two team.


class GamePlay
{
private:

	// BlackHole for the game.
	BlackHole BHole;

	// Gamemode 0 means man vs ai, 1 measn man vs man.
	int GameMode = 0;

	// Related to choose mode.
	Font ModeChooseFont;
	Text ModeChooseTxt;

	// SoundManager.
	SoundManager MySoundManager;

	// Background.
	Sprite BGSprite;
	Texture BGTexture;

	// Related to time tracking.
	Clock ClockObj;

	// 0 means in game, 1 means scoring, 2 means winning, 3 means chosing mode.
	int GameState = 3;

	float ScoreTime = 3000; // millisecond 

	float ScoreEndTime = 0; // millisecond 

	float PadSpeed = 200;

	// This is used to move the ball and the pad.
	Clock clock;

	PadController MyController;

	// Ball speed.
	float BallStartSpeed = 5;

	float AddSpeed = 1;

	// Related to score of each team.
	Font ScoreFont;
	int WinningScore = 5;
	
	Text BlueScoreTxt;
	int BlueScore = 0;

	Text RedScoreTxt;
	int RedScore = 0;

	Font ScoreAndWinFont;
	Text ScoreAndWinText;

	Ball MyBall;

	// Record the recent score team.
	// 0 means BlueTeam, 1 means RedTeam.
	int ScoreFlag = 0;

	int CheckBallMove();

	// AI player.
	AIPlayer AIPlayerObj;

	// Use this direction when I am sure they collided.
	Vector2f GetBouncingDirection(float ballX, float ballY, float ballPosY, float padPosX, float padPosY, float padWidth, float padHeight, float radius);

	// Drag to the black hole.
	void DragToTheBlackhole(Ball &ballObj, BlackHole &blackholeObj, float deltaTime);

public:
	// Hanlde ball move and pad move.
	int PlayGame();
	
	// Handle score check.
	int Score();
	
	// Handle winning congratulation.
	int Winning();

	// Pop up button for choose modes.
	int ChooseMode(RenderWindow *windobObj);

	int GetGameState() { return GameState; };

	int Render(RenderWindow *windowObj);

	Ball GetBall() { return MyBall; };

	PadController GetPadController() { return MyController; };

	GamePlay();
	~GamePlay();
};

