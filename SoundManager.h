#pragma once
#include <sfml/Audio.hpp>
#include <sfml/Config.hpp>

using namespace sf;

class SoundManager
{
private:
	Music BGMusic;

	Sound HitPad;
	SoundBuffer HitPadBuff;

	Sound HitWall;
	SoundBuffer HitWallBuff;

	Sound Score;
	SoundBuffer ScoreBuff;

	Sound Win;
	SoundBuffer WinBuff;

public:
	void PlayBG();
	void PlayHitPad();
	void PlayHitWall();
	void PlayScore();
	void PlayWin();

	SoundManager();
	~SoundManager();
};

