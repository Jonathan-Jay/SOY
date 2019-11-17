#include "AnimatronicMove.h"

Animatronic Freddy;
Animatronic Chica;
Animatronic Bonnie;
Animatronic Foxy;

void characterMove() 
{
	timeElapsed = std::time(0) - timeAtStart;
	int timeBetween = 5; //Five seconds for an example
	if (timeElapsed >= timeBetween)
	{
		positionChange(Freddy);
	}
	if (timeElapsed >= timeBetween)
	{
		positionChange(Chica);
	}
	if (timeElapsed >= timeBetween)
	{
		positionChange(Bonnie);
		timeAtStart = std::time(0);
	}
	//Foxy is a special case
	//Same with golden freddy
}