#include "Animatronic.h"

//Return true if the animatronic is ok to move, else false -> don't move.
bool doMove(Animatronic AnimatronicName)
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
	if (move) 
	{
		switch (AnimatronicName.position)
		{
		case 1:
			AnimatronicName.position = 8;
			break;
		case 2:
			int rng = rand() % 3;
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
			int rng = rand() % 2;
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
			int rng = rand() % 3;
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
			int rng = rand() % 3;
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