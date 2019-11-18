#include "Animatronic.h"
Animatronic Freddy;
Animatronic Chica;
Animatronic Bonnie;
Animatronic Foxy;
int timeStart = time(0);
int timeAfter;
bool isRun = true;

void initializeAnimatronics() //To initialize all of the animatronics things
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
		Freddy.difficulty = 10;
		Chica.difficulty = 10;
		Bonnie.difficulty = 10;
		Foxy.difficulty = 10;

	}

}

//Return true if the animatronic is ok to move, else false -> don't move.
bool doMove(Animatronic& AnimatronicName)
{
	srand(time(NULL));
	int random = rand();
	random %= 100;
	if (AnimatronicName.difficulty > random)
	{
		return true;
	}
	return false;
}

int positionChange(Animatronic& AnimatronicName)
{
	//if they the animatronic move position
	//POSITION == CAMERA THAT THEY SHOULD BE ON

	//DEV NOTES REMOVE BEFORE SUBMISSION(OR PATCH): Fairly certain there is a chance that no movement happens with the random
	bool move = doMove(AnimatronicName);
	int rng;
	if (move)
	{
		switch (AnimatronicName.position)
		{
		case 1:
			AnimatronicName.position = 8;
			break;
		case 2:
			rng = rand() % 3;
			if (rng == 1)
			{
				AnimatronicName.position = 8;
			}
			else if (rng == 2)
			{
				AnimatronicName.position = 4;
			}
			else if (rng == 3)
			{
				AnimatronicName.position = 6;
			}
			break;

		case 3:
			AnimatronicName.position = 8;
			break;
		case 4:
			AnimatronicName.position = 2;
			break;
		case 5:
			rng = rand() % 2;
			if (rng == 1)
			{
				AnimatronicName.position = 8;
			}
			else if (rng == 2)
			{
				AnimatronicName.position = 9;
			}
			break;
		case 6:
			rng = rand() % 3;
			if (rng == 1)
			{
				AnimatronicName.position = 2;
			}
			else if (rng == 2)
			{
				AnimatronicName.position = 7;
			}
			else if (rng == 3)
			{
				AnimatronicName.position = 9;
			}
			break;
		case 7:
			break;
		case 8:
			rng = rand() % 3;
			if (rng == 1)
			{
				AnimatronicName.position = 1;
			}
			else if (rng == 2)
			{
				AnimatronicName.position = 5;
			}
			else if (rng == 3)
			{
				AnimatronicName.position = 2;
			}
			break;
		case 9:
			//JUMPSCARE!!!
			break;
		default:
			break;
		}
	}

	return 0;
}

void Animatronic::changePosition()
{
	timeAfter = std::time(0) - timeStart;
	int timeBetween = 5; //Five seconds for an example
	if (timeAfter >= timeBetween)
	{
		positionChange(Freddy);
		positionChange(Chica);
		positionChange(Bonnie);
		timeAfter = std::time(0);
	}
	//Foxy is a special case
	//Same with golden freddy
}
