#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <conio.h>
#include <string>

class Soundfunctions
{
public:
	void PlaySingleSound(std::string Filename);
	void LoopSound(std::string Filename); //Loops Sound
	void PauseSound(std::string Filename); //Stops sound
	void LoadSound(std::string Filename); //Used to preload sounds during init
	void PlaySoundWait(std::string Filename); //Plays a sound & waits until it's done before doing the next command
};