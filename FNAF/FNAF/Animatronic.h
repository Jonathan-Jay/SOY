#pragma once
#include <chrono>
#include <ctime> 

class Animatronic
{
public:
	int animatronicNB; //Who is the animatronic. For the other cpps
	int difficulty; //Out of 100 -> 100 Equals Hardest, 0 Is easiest.
	int position = 0; //their position, this is more useful for other cpps

private:


};

std::time_t timeAtStart = std::time(0);

std::time_t timeElapsed;

bool doMove(Animatronic AnimatronicName);

int positionChange(Animatronic AnimatronicName);
