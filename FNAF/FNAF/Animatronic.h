#pragma once
#include <chrono>
#include <ctime> 
#include "Map.h"

class Animatronic
{
public:
	int animatronicNB; //Who is the animatronic. For the other cpps
	int difficulty; //Out of 100 -> 100 Equals Hardest, 0 Is easiest.
	int position = 0; //their position, this is more useful for other cpps

private:


};

auto timeAtStart = std::chrono::system_clock::now();

auto timeElapsed = std::chrono::system_clock::now() - timeAtStart;

bool doMove(Animatronic AnimatronicName);

int positionChange(Animatronic AnimatronicName);
