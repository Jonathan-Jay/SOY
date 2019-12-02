#pragma once
#include <chrono>
//#include <ctime> 
#include "Timer.h"
#include <time.h>

class Animatronic
{
public:
	int animatronicNB; //Who is the animatronic. For the other cpps
	int difficulty = 0; //Out of 100 -> 100 Equals Hardest, 0 Is easiest. Foxy Must be at least 1,
	int position; //their position, this is more useful for other cpps
	static void changePosition(int onCamera, int, bool x[], bool y, float &power);

private:


};	

void initializeAnimatronics(int, int, int);
void Difficulty(int freddyDifficulty, int difficulty);
bool doMove(Animatronic& AnimatronicName);
	
	int positionChange(Animatronic& AnimatronicName, int onCamera, bool x[], bool y, float power);

	int* returnPosition();
	