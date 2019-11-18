#pragma once
#include <chrono>
//#include <ctime> 
#include "Timer.h"
#include <time.h>

class Animatronic
{
public:
	int animatronicNB; //Who is the animatronic. For the other cpps
	int difficulty; //Out of 100 -> 100 Equals Hardest, 0 Is easiest.
	int position = 8; //their position, this is more useful for other cpps
	static void changePosition();

private:


};	
void initializeAnimatronics();
bool doMove(Animatronic& AnimatronicName);
	
	int positionChange(Animatronic& AnimatronicName);
