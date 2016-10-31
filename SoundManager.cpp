#include "SoundManager.h"

void SoundManager::PlayBG()
{
	BGMusic.play();
}

void SoundManager::PlayHitPad()
{
	HitPad.play();
}

void SoundManager::PlayHitWall()
{
	HitWall.play();
}

void SoundManager::PlayScore()
{
	Score.play();
}

void SoundManager::PlayWin()
{
	Win.play();
}

SoundManager::SoundManager()
{
	if (!BGMusic.openFromFile("Sound/Tenderness of hands.wav"))
	{
		printf("What the hack is going on here ?");
	}
	BGMusic.setLoop(true);

	// Set Buff for other sound.
	HitWallBuff.loadFromFile("Sound/wall_bounce.wav");
	HitPadBuff.loadFromFile("Sound/paddle_bounce.wav");
	ScoreBuff.loadFromFile("Sound/score.wav");
	WinBuff.loadFromFile("Sound/victory.wav");

	HitWall.setBuffer(HitWallBuff);
	HitPad.setBuffer(HitPadBuff);
	Score.setBuffer(ScoreBuff);
	Win.setBuffer(WinBuff);
}


SoundManager::~SoundManager()
{
}
