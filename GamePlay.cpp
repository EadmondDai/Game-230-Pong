#include "GamePlay.h"

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

	// Get the ball location to AI and let AI do the movong.
	// AI need two object. Ball and the pad.
	AIPlayerObj.ChaseTheBall(&MyBall, &MyController.GetRedPad(), &MyController, deltaTime, PadSpeed);

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
		printf(" what the fuck?");
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
		Vector2f newDirection = GetBouncingDirection(ballDirection.x, ballDirection.y, posY, padPosXR, padPosYR, padWidthR, padHeightR, radius);
		MyBall.SetDirection(newDirection.x, newDirection.y);
		MyBall.AddSpeed(AddSpeed);
	}

	// Check if the ball is out of the left or right boundary.
	if (posX + radius * 2 < 0)
	{
		RedScore++;
		RedScoreTxt.setString(to_string(RedScore));
		ScoreFlag = 1;

		if (RedScore >= WinningScore)
		{
			GameState = 2;
		}
		else
		{
			ScoreEndTime = ClockObj.getElapsedTime().asMilliseconds() + ScoreTime;
			GameState = 1;
		}
		return 0;
	}

	if (posX > 800)
	{
		BlueScore++;
		BlueScoreTxt.setString(to_string(BlueScore));
		ScoreFlag = 0;

		if (BlueScore >= WinningScore)
		{
			GameState = 2;
		}
		else
		{
			ScoreEndTime = ClockObj.getElapsedTime().asMilliseconds() + ScoreTime;
			GameState = 1;
		}
		return 0;
	}

	MyBall.Move();

	return 0;
}

Vector2f GamePlay::GetBouncingDirection(float ballX, float ballY, float ballPosY, float padPosX, float padPosY, float padWidth, float padHeight, float radius)
{
	// Check the directions of the ball and the pad.
	// I need to change X direction, that's for sure.
	float returnX;
	float returnY = 0;;
	Vector2f returnDirection;

	// Since I deceteced they collided, so I only need to change X direction.
	returnX = -ballX;

	// Then get the Y direction according to the pad.
	// I need to adjust the amount for Y turing.
	if ((ballPosY + radius) < (padPosY + padHeight / 2))
	{
		returnY = ballY + (ballPosY + radius - padPosY - padHeight / 2) / padHeight * 2;
	}
	else if ((ballPosY + radius) > (padPosY + padHeight / 2))
	{
		returnY = ballY + (ballPosY + radius - padPosY - padHeight / 2) / padHeight * 2;
	}

	// And last, adding Y volecity to the ball.


	// Need to normallize the direction.
	//float length = sqrtf(returnX * returnX + returnY * returnY);
	//returnDirection.x = returnX / length;
	//returnDirection.y = returnY / length;
	returnDirection.x = returnX;
	returnDirection.y = returnY;

	return returnDirection;
}

int GamePlay::Score()
{
	// Show something.
	if (ScoreFlag == 0)
	{
		ScoreAndWinText.setString("Blue Team scored!");
	}
	else
	{
		ScoreAndWinText.setString("Red Team scored!");
	}

	// I should change gamestate back.
	if (ScoreEndTime != 0 && ClockObj.getElapsedTime().asMilliseconds() >= ScoreEndTime)
	{
		ScoreEndTime = 0;
		GameState = 0;

		MyBall.InitPos();
		MyController.InitPadsPos();

		ScoreAndWinText.setString("");
	}

	return 0;
}

int GamePlay::Winning()
{
	// Show something.
	if (ScoreFlag == 0)
	{
		ScoreAndWinText.setString("Blue Team Won!");
	}
	else
	{
		ScoreAndWinText.setString("Red Team Won!");
	}

	// I should change gamestate back here.

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

	// Show the words for congruatulate the scoring team.
	if (GameState == 1 || GameState == 2)
	{
		windowObj->draw(ScoreAndWinText);
	}

	windowObj->display();

	return 0;
}

GamePlay::GamePlay()
{
	ScoreFont.loadFromFile("Font/HARLOWSI.TTF");
	ScoreAndWinFont.loadFromFile("Font/GIGI.TTF");

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

	ScoreAndWinText.setCharacterSize(90);
	ScoreAndWinText.setColor(Color::White);
	ScoreAndWinText.setPosition(400 - 300, 300 - 100);
	ScoreAndWinText.setFont(ScoreAndWinFont);
	
	MyBall.SetSpeed(BallStartSpeed);
}


GamePlay::~GamePlay()
{

}
