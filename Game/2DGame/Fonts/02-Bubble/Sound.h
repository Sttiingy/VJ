#pragma once
#include <string>
class Sound
{
public:
	static Sound &instance()
	{
		static Sound G;
		return G;
	}

	Sound();
	~Sound();
	void playMusic(char *url);
	void stopMusic();
	void jumpEffect();
	void stopEffect();
private:

	void init();



};