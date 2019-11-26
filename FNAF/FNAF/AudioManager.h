#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <conio.h>
#include <string>

class Soundfunctions
{
public:
	void PlaySingleSound(std::string Filename);
	void LoopSound(std::string Filename);
	void PauseSound(std::string Filename);
};