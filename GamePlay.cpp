#include "GamePlay.h"


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

	MyBall.Move();

	return 0;
}

int GamePlay::Score()
{
	return 0;
}

int GamePlay::Winning()
{
	return 0;
}

GamePlay::GamePlay()
{

}


GamePlay::~GamePlay()
{

}
