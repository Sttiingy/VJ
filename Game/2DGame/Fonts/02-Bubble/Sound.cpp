#include "Sound.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <irrKlang.h>
#include <vector>

using namespace irrklang;



ISoundEngine* engineMusic;
ISoundEngine* engineEffects;
ISound* music;
ISound* effect;

Sound::Sound()
{
	init();
}

Sound::~Sound()
{
	music->drop();
	engineEffects->drop();
	engineMusic->drop();

}


void Sound::playMusic(char *url)
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D(url, true, false, true);
	music->setVolume(0.1f);
}

void Sound::stopMusic() {
	engineMusic->stopAllSounds();
}

void Sound::jumpEffect()
{
	effect = engineEffects->play2D("sounds/JumpFX.wav", false, false, true);
	effect->setVolume(0.15f);
}

void Sound::dashEffect()
{
	effect = engineEffects->play2D("sounds/DashFX.wav", false, false, true);
	effect->setVolume(0.15f);
}

void Sound::back2LifeEffect()
{
	effect = engineEffects->play2D("sounds/Back2Life.wav", false, false, true);
	effect->setVolume(0.15f);
}

void Sound::BoingEffect() {
	effect = engineEffects->play2D("sounds/Boing.wav", false, false, true);
	effect->setVolume(0.15f);
}

void Sound::DeathEffect() {
	effect = engineEffects->play2D("sounds/DeathFX.wav", false, false, true);
	effect->setVolume(0.35f);
}

void Sound::init() {
	engineMusic = createIrrKlangDevice();
	engineEffects = createIrrKlangDevice();
}

void Sound::stopEffect() {
	engineEffects->stopAllSounds();
}

void Sound::WinEffect() {
	effect = engineEffects->play2D("sounds/Win.wav", false, false, true);
	effect->setVolume(0.15f);
}

