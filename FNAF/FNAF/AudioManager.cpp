#include "AudioManager.h"

void Soundfunctions::PlaySingleSound(std::string Filename)
{
	std::string SoundString = "play assets/Audio_Files/" + Filename + " wait";
	mciSendString(SoundString.c_str(), NULL, 0, NULL);
}

void Soundfunctions::LoopSound(std::string Filename)
{
	std::string SoundString = "play assets/Audio_Files/" + Filename + " repeat";
	mciSendString(SoundString.c_str(), NULL, 0, NULL);
}
void Soundfunctions::PauseSound(std::string Filename)
{
	std::string SoundString = "stop assets/Audio_Files/" + Filename;
	mciSendString(SoundString.c_str(), NULL, 0, NULL);
}

void Soundfunctions::LoadSound(std::string Filename)
{
	std::string SoundString = "open assets/Audio_Files/" + Filename + " type mpegvideo alias mp3";
	mciSendString(SoundString.c_str(), NULL, 0, NULL);
}

void Soundfunctions::PlaySoundWait(std::string Filename)
{
	std::string SoundString = "play " + Filename + " wait";
	mciSendString(SoundString.c_str(), NULL, 0, NULL);
}
