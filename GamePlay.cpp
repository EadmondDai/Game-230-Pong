#include "GamePlay.h"
#include <iostream>

using namespace std;

int GamePlay::PlayGame()
{

	float deltaTime = clock.restart().asSeconds();

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		MyController.MovePad(0, -deltaTime * PadSpeed, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		MyController.MovePad(0, deltaTime * PadSpeed, 0);
	}

	CheckBallMove();

	return 0;
}

int GamePlay::CheckBallMove()
{
	// Check if the ball hit anything it can collide with.
	// If hit the wall or the pad, change direction or add speed.

	float posX = MyBall.GetPosX();
	float posY = MyBall.GetPosY();
	float radius = MyBall.GetRadius();
	Vector2f ballDirection = MyBall.GetDirection();

	// If hit the upper and the lower wall, just bounce back.
	Vector2f direction = MyBall.GetDirection();

	if (posY <= 0 && direction.y < 0)
	{
		MyBall.SetDirection(direction.x, -direction.y);
	}

	if (posY + MyBall.GetRadius() * 2 >= 600 && direction.y > 0)
	{
		MyBall.SetDirection(direction.x, -direction.y);
	}

	// Check if hit the pad, and handle the rest.
	// First, check if hit the left pad.
	Pad bluePad = MyController.GetBluePad();
	float padPosX = bluePad.GetX();
	float padPosY = bluePad.GetY();
	float padWidth = bluePad.GetWidth();
	float padHeight = bluePad.GetHeight();

	if ((posX >= padPosX && posX <= padPosX + padWidth) && (posY + radius * 2 >= padPosY  && posY <= padPosY + padHeight) && direction.x < 0)
	{
		Vector2f newDirection = GetBouncingDirection(ballDirection.x, ballDirection.y, posY, padPosX, padPosY, padWidth, padHeight, radius);
		MyBall.SetDirection(newDirection.x, newDirection.y);
		MyBall.AddSpeed(AddSpeed);
	}

	// Then the right pad.
	Pad redPad = MyController.GetRedPad();
	float padPosXR = redPad.GetX();
	float padPosYR = redPad.GetY();
	float padWidthR = redPad.GetWidth();
	float padHeightR = redPad.GetHeight();

	if ((posX + radius * 2 >= padPosXR && posX + radius * 2 <= padPosXR + padWidthR) && (posY + radius * 2 >= padPosYR  && posY <= padPosYR + padHeightR) && direction.x > 0)
	{
		Vector2f newDirection = GetBouncingDirection(ballDirection.x, ballDirection.y, posY, padPosX, padPosY, padWidth, padHeight, radius);
		MyBall.SetDirection(newDirection.x, newDirection.y);
		MyBall.AddSpeed(AddSpeed);
	}


	MyBall.Move();

	return 0;
}

Vector2f GamePlay::GetBouncingDirection(float ballX, float ballY, float ballPosY, float padPosX, float padPosY, float padWidth, float padHeight, float radius)
{
	// Check the directions of the ball and the pad.
	// I need to change X direction, that's for sure.
	float returnX;
	float returnY;
	Vector2f returnDirection;

	// Since I deceteced they collided, so I only need to change X direction.
	returnX = -ballX;

	// Then get the Y direction according to the pad.
	// I need to adjust the amount for Y turing.
	if ((ballPosY + radius) < (padPosY + padHeight / 2))
	{
		returnY = ballY + (padPosY + radius - ballPosY - padHeight / 2) / padHeight * 2;
	}
	else if ((ballPosY + radius) > (padPosY + padHeight / 2))
	{
		returnY = ballY - (padPosY + radius - ballPosY - padHeight / 2) / padHeight * 2;
	}

	// And last, adding Y volecity to the ball.


	// Need to normallize the direction.
	float length = sqrtf(returnX * returnX + returnY * returnY);
	returnDirection.x = returnX / length;
	returnDirection.y = returnY / length;

	return returnDirection;
}

int GamePlay::Score()
{
	return 0;
}

int GamePlay::Winning()
{
	return 0;
}

int GamePlay::Render(RenderWindow *windowObj)
{
	windowObj->clear();

	// This is the score of each team.
	windowObj->draw(BlueScoreTxt);

	windowObj->draw(RedScoreTxt);

	// This is two pad
	RectangleShape blueShape = MyController.GetBlueShape();
	blueShape.setFillColor(Color::Blue);
	blueShape.setOutlineColor(Color::Cyan);

	windowObj->draw(blueShape);

	RectangleShape redShape = MyController.GetRedShape();
	redShape.setFillColor(Color::Red);
	redShape.setOutlineColor(Color::Magenta);

	windowObj->draw(redShape);

	// This is the ball.
	CircleShape ball = GetBall().GetBallShape();
	ball.setFillColor(Color::Green);
	windowObj->draw(ball);


	windowObj->display();

	return 0;
}

GamePlay::GamePlay()
{
	ScoreFont.loadFromFile("Font/HARLOWSI.TTF");
	
	BlueScoreTxt.setCharacterSize(60);
	BlueScoreTxt.setColor(Color::Cyan);
	BlueScoreTxt.setPosition(175, 50);
	BlueScoreTxt.setFont(ScoreFont);
	BlueScoreTxt.setString(to_string(BlueScore));

	RedScoreTxt.setCharacterSize(60);
	RedScoreTxt.setColor(Color::Magenta);
	RedScoreTxt.setPosition(575, 50);
	RedScoreTxt.setFont(ScoreFont);
	RedScoreTxt.setString(to_string(RedScore));

	MyBall.SetSpeed(BallStartSpeed);
}


GamePlay::~GamePlay()
{

}
