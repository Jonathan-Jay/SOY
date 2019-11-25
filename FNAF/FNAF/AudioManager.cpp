#include "AudioManager.h"

void PlaySingleSound(std::string Filename)
{
	std::string test = "play assets/Audio_Files/" + Filename + " wait";
	mciSendString(test.c_str(), NULL, 0, NULL);
}
