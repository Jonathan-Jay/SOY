#include "Animatronic.h"
#include <iostream>
Animatronic Freddy;
Animatronic Chica;
Animatronic Bonnie;
Animatronic Foxy;
int timeStart = time(0);
int timeAfter = std::time(0) - timeStart;
int deltaTime = std::time(0);
int timeOfNight = 0;

float onCamTime = 0.f;
float deltaOnCam = Timer::currentClock;

bool isRun = true;

void initializeAnimatronics(int difficulty) //To initialize all of the animatronics things
{
	if (isRun)
	{
		isRun = false;
		//Initializing the number
		Freddy.animatronicNB = 0;
		Chica.animatronicNB = 1;
		Bonnie.animatronicNB = 2;
		Foxy.animatronicNB = 3;
		//foxy's position is different than the rest of the animatronic
		Foxy.position = 1;
		//difficulty
		Freddy.difficulty = difficulty;
		Chica.difficulty = difficulty;
		Bonnie.difficulty = difficulty;
		Foxy.difficulty = difficulty;

	}

}

//Return true if the animatronic is ok to move, else false -> don't move.
bool doMove(Animatronic& AnimatronicName)
{
	//srand(time(NULL));
	int random = rand() % 100;
	if (AnimatronicName.difficulty > random)
	{
		return true;
	}
	return false;
}

int positionChange(Animatronic& AnimatronicName, int onCamera)
{
	//if they the animatronic move position
	//POSITION == CAMERA THAT THEY SHOULD BE ON


	int rng;

	//freddy
	if ((AnimatronicName.animatronicNB == 0) && (AnimatronicName.position != onCamera))
	{
		switch (AnimatronicName.position)
		{
		case 3:
			AnimatronicName.position = 8;
			break;
		case 8:
			AnimatronicName.position = 2;
			break;
		case 2:
			AnimatronicName.position = 6;
			break;
		case 6:
			AnimatronicName.position = 10; //blindspot on the left
			break;
		case 10:
			//if time passes, and there is no door, then jumpscare
			//but door is back closed then back at
			break;
		}
		std::cout << AnimatronicName.animatronicNB << ":" << AnimatronicName.position << "\n";
	}//Bonnie
	else if (AnimatronicName.animatronicNB == 2)
	{
		switch (AnimatronicName.position)
		{
		case 3:
			AnimatronicName.position = 8;
			break;
		case 8:
			AnimatronicName.position = 2;
			break;
		case 2:
			rng = rand() % 2 + 1;
			if (rng == 1)
			{
				AnimatronicName.position = 4;
			}
			else if (rng == 2)
			{
				AnimatronicName.position = 5;
			}
			break;
		case 5:
			AnimatronicName.position = 9; // on the left side
			break;
		case 4:
			AnimatronicName.position = 2;
		case 9:
			//if time passes, and there is no door, then jumpscare
			break;

		default:
			break;
		}
		std::cout << AnimatronicName.animatronicNB << ":" << AnimatronicName.position << "\n";
	}
	//Chica
	else if (AnimatronicName.animatronicNB == 1)
	{
		switch (AnimatronicName.position)
		{
		case 3:
			AnimatronicName.position = 8;
			break;
		case 8:
			AnimatronicName.position = 2;
			break;
		case 2:
			AnimatronicName.position = 6;
			break;
		case 6:
			rng = rand() % 2 + 1;
			if (rng == 1)
			{
				AnimatronicName.position = 10; //blindspot on the left
			}
			else if (rng == 2)
			{
				AnimatronicName.position = 7;
			}
			break;
		case 7:
			AnimatronicName.position = 6;
			break;
		case 10:
			//if time passes, and there is no door, then jumpscare
			//but door is back closed then back at
			break;

		default:
			break;
		}
		std::cout << AnimatronicName.animatronicNB << ":" << AnimatronicName.position << "\n";


	}

	if ((AnimatronicName.animatronicNB == 3) && (onCamera != 1))
	{
		if (onCamTime >= 60000)
		{
			AnimatronicName.position++;
		}
	}
	return 0;
}

void Animatronic::changePosition(int onCamera, int timeOfNight)
{
	timeAfter = std::time(0) - deltaTime;
	int timeBetween = (std::rand() % 5) + 5; //Five seconds for an example
	if (timeAfter >= timeBetween)
	{
		bool move = doMove(Freddy);
		if (move)
		{
			positionChange(Freddy, onCamera);
			move = false;
		}
		move = doMove(Chica);
		if (move)
		{
			positionChange(Chica, onCamera);
			move = false;
		}
		move = doMove(Chica);
		if (move)
		{
			positionChange(Bonnie, onCamera);
			move = false;
		}

		deltaTime = std::time(0);
	}
	positionChange(Foxy, onCamera);
	//foxy camera things
	if (onCamera == 1)
	{
		onCamTime += Timer::currentClock - deltaOnCam;
	}
	else
	{
		deltaOnCam = Timer::currentClock;
	}
	//Foxy is a special case
}
