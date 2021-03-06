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
	if(GameMode == 1)
	{
		AIPlayerObj.ChaseTheBall(&MyBall, &MyController.GetRedPad(), &MyController, deltaTime, PadSpeed);
	}
	else if (GameMode == 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			MyController.MovePad(0, -deltaTime * PadSpeed, 1);
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			MyController.MovePad(0, deltaTime * PadSpeed, 1);
		}
	}

	CheckBallMove();

	// After ball move, drag the ball to the black ball.

	DragToTheBlackhole(MyBall, BHole, deltaTime);

	return 0;
}

void GamePlay::DragToTheBlackhole(Ball &ballObj, BlackHole &blackholeObj, float deltaTime)
{
	float ballX = ballObj.GetPosX();
	float ballY = ballObj.GetPosY();
	float ballRadius = ballObj.GetRadius();
	Vector2f ballDirection = ballObj.GetDirection();

	float blackX = blackholeObj.GetPosX();
	float blackY = blackholeObj.GetPosY();
	float blackRadius = blackholeObj.GetRadius();
	float gravity = blackholeObj.GetGravity();
	float range = blackholeObj.GetRange();

	// Only within the range will the blackhole take effect.
	// Change the direction and the speed of the ball to mimic the black hole.
	float diffX = blackX - ballX - ballRadius;
	float diffY = blackY - ballY - ballRadius;

	float distance = sqrtf(diffX * diffX + diffY * diffY);
	
	if (distance < range)
	{
		float travelUnit = (1 - distance / range) * gravity;

		float directionX =  (diffX * abs(diffX)) / (distance * distance);
		float directionY = (diffY * abs(diffY)) / (distance * distance);
		float directionXUnit = directionX * (1 - distance / range);
		float directionYUnit = directionY * (1 - distance / range);

		ballObj.SetDirection(ballDirection.x + directionX * deltaTime, ballDirection.y + directionY * deltaTime);
	}
}

int GamePlay::CheckBallMove()
{
	// Check if the ball hit anything it can collide with.
	// If hit the wall or the pad, change direction or add speed.

	float posX = MyBall.GetPosX();
	float posY = MyBall.GetPosY();
	float radius = MyBall.GetRadius();
	Vector2f ballDirection = MyBall.GetDirection();

	TestTrail.append(Vertex(Vector2f(posX + radius, posY + radius)));

	// If hit the upper and the lower wall, just bounce back.
	Vector2f direction = MyBall.GetDirection();

	if (posY <= 0 && direction.y < 0)
	{
		MyBall.SetDirection(direction.x, -direction.y);

		MySoundManager.PlayHitWall();
	}

	
	if (posY + MyBall.GetRadius() * 2 >= 600 && direction.y > 0)
	{
		MyBall.SetDirection(direction.x, -direction.y);

		MySoundManager.PlayHitWall();
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

		MySoundManager.PlayHitPad();
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

		MySoundManager.PlayHitPad();
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

			MySoundManager.PlayWin();
		}
		else
		{
			ScoreEndTime = ClockObj.getElapsedTime().asMilliseconds() + ScoreTime;
			GameState = 1;

			MySoundManager.PlayScore();
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

			MySoundManager.PlayWin();
		}
		else
		{
			ScoreEndTime = ClockObj.getElapsedTime().asMilliseconds() + ScoreTime;
			GameState = 1;

			MySoundManager.PlayScore();
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
	//returnDirection.x = returnX * returnX / length * length;
	//returnDirection.y = returnY * returnY / length * length;
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

	// I need to restart time here, to prevent AIPlayer going wild.
	clock.restart().asSeconds();

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

	// I should change gamestate back here and init the game again.
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		BlueScore = 0;
		RedScore = 0;
		BlueScoreTxt.setString(to_string(BlueScore));
		RedScoreTxt.setString(to_string(RedScore));

		GameState = 3;

		MyBall.InitPos();
		MyController.InitPadsPos();

		TestTrail.clear();
	}

	// Apity, I have to restart the clock here too.
	clock.restart().asSeconds();

	return 0;
}

int GamePlay::ChooseMode(RenderWindow *windowObj)
{
	// This place handle all the mode choice.
	ModeChooseTxt.setString("Before start the game, you can choose to play\n player vs player mode by pressing 'y', pressing\n 'n' will play on default mode.");

	windowObj->clear();

	windowObj->draw(ModeChooseTxt);

	windowObj->display();

	if (Keyboard::isKeyPressed(Keyboard::Y))
	{
		GameState = 0;
		GameMode = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::N))
	{
		GameState = 0;
		GameMode = 1;
	}

	// In case the ai pad go wild.
	clock.restart().asMilliseconds();

	return 0;
}

int GamePlay::Render(RenderWindow *windowObj)
{
	windowObj->clear();

	// Background sprite.
	windowObj->draw(BGSprite);

	windowObj->draw(TestTrail);

	// Black hole.
	CircleShape blackHole = BHole.GetMyShape();
	blackHole.setFillColor(Color::Black);
	windowObj->draw(blackHole);

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

	// Background
	BGTexture.loadFromFile("Pic/background.jpg");
	

	BGSprite.setPosition(0, 0);
	BGSprite.setTexture(BGTexture);
	BGSprite.setScale(0.416, 0.555);

	// Start Background music.
	MySoundManager.PlayBG();

	// Related to choosing a play mode.
	ModeChooseFont.loadFromFile("Font/GIGI.TTF");
	ModeChooseTxt.setFont(ModeChooseFont);
	ModeChooseTxt.setPosition(400 - 300, 300 - 100);
	ModeChooseTxt.setColor(Color(8, 37, 103));

	// Set up blackhole.
	BHole.SetPos(400, 300);

}


GamePlay::~GamePlay()
{

}
