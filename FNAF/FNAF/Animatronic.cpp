#include "Animatronic.h"
#include "AudioManager.h"
#include <iostream>
Animatronic Freddy;
Animatronic Chica;
Animatronic Bonnie;
Animatronic Foxy;

int timeAfter = 0;
int deltaTime = 0;
int timeOfNight = 0;
int hitcount = 0;
long float onCamTime = 0.f;
long float deltaOnCam = time(0);
float foxyRunTime = 0;
int nightNumber = 0;
int positionCounterByMovement = 1;

bool bruhMoment = true; //because for some reason foxy would move twice even though he should only move once. I don't know why and Time is too close to try to come up with something better
void initializeAnimatronics(int difficulty, int night, int freddyDifficulty) //To initialize all of the animatronics things
{
	bruhMoment = true;
	nightNumber = night;
	srand(time(NULL));
	//Initializing the variables
	timeAfter = 0;
	deltaTime = 0;
	timeOfNight = 0;
	hitcount = 0;
	onCamTime = 0.f;
	deltaOnCam = Timer::currentClock;
	positionCounterByMovement = 1;

	//Initializing the number
	Freddy.animatronicNB = 0;
	Chica.animatronicNB = 1;
	Bonnie.animatronicNB = 2;
	Foxy.animatronicNB = 3;
	//Initialzes positions if the night changes
	Freddy.position = 3;
	Chica.position  = 3;
	Bonnie.position = 3;
	Foxy.position = 1;
	//difficulty
	Freddy.difficulty = freddyDifficulty;
	Chica.difficulty = difficulty;
	Bonnie.difficulty = difficulty;
	Foxy.difficulty = difficulty;



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

int positionChange(Animatronic& AnimatronicName, int onCamera, bool isDoorDown[], bool playerOnCamera, float power)
{
	//if they the animatronic move position
	//POSITION == CAMERA THAT THEY SHOULD BE ON


	int rng;

	//freddy
	if ((AnimatronicName.animatronicNB == 0) && !(AnimatronicName.position == onCamera && (playerOnCamera || power <= 0)))
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
			if (isDoorDown[3])
			{
				AnimatronicName.position = 6;
			}
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
			if (isDoorDown[2])
			{
				AnimatronicName.position = 8;
			}
			
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
			if (isDoorDown[3])
			{
				AnimatronicName.position = 8;
			}

			break;

		default:
			break;
		}
		std::cout << AnimatronicName.animatronicNB << ":" << AnimatronicName.position << "\n";
		if ((playerOnCamera) && (Chica.position == 10) && !(isDoorDown[3]))
		{
			std::cout << "Chica is in the office\n";
			Chica.position = 11;
		}
		else if ((playerOnCamera) && (Bonnie.position == 9) && !(isDoorDown[2]))
		{
			std::cout << "Bonnie is in the office\n";
			Bonnie.position = 11;
		}
		else if ((playerOnCamera) && (Freddy.position == 10) && !(isDoorDown[3]))
		{
			std::cout << "Freddy is in the office\n";
			Freddy.position = 11;
		}

	}
	
	//Foxy
	if ((AnimatronicName.animatronicNB == 3) && !(onCamera == 1 && playerOnCamera))
	{
		if ((float)timeOfNight / (float)positionCounterByMovement >= 100 / nightNumber)
		{
			if (bruhMoment)
			{
				bruhMoment = false;
				if (onCamTime <= nightNumber)
				{
					positionCounterByMovement++;
					timeOfNight++;
					if (Foxy.position <= 5)
					{
						AnimatronicName.position++;
					}
				}
				onCamTime = 0;
				std::cout << AnimatronicName.animatronicNB << ":" << AnimatronicName.position << "\n";
			}
			else 
			{
				bruhMoment = true;
			}

		}
	}
	return 0;
}

void Animatronic::changePosition(int onCamera, int _timeOfNight, bool isDoorDown[], bool playerOnCamera, float &power)
{
	timeOfNight = _timeOfNight;
	//This is to run the Jumpscare AI if the time comes
	

	if (Foxy.position >= 5)
	{
		if (foxyRunTime >= 3)
		{
			if (isDoorDown[2])
			{
				Foxy.position = 1;
				
				//reduce power by 5 times amount of times hit + 1, then increase amount of times hit by 1 (post addition)
				power -= 5 * hitcount++ + 1;
				Soundfunctions().PlaySingleSound("Foxy_Knock.mp3");
			}
			else
			{
				Foxy.position = 11;
			}
		}
		foxyRunTime += Timer::deltaTime;
	}
	else
	{
		foxyRunTime = 0;
	}

	//Time for AI related things
	if (deltaTime == 0)
		deltaTime = time(0);
	timeAfter = time(0) - deltaTime;
	int timeBetween = (std::rand() % 5) + 5; //Five seconds for an example
	if (timeAfter >= timeBetween)
	{
		bool move = doMove(Freddy);
		if (move)
		{
			positionChange(Freddy, onCamera, isDoorDown, playerOnCamera, power);
			move = false;
		}
		move = doMove(Chica);
		if (move)
		{
			positionChange(Chica, onCamera, isDoorDown, playerOnCamera);
			move = false;
		}
		move = doMove(Bonnie);
		if (move)
		{
			positionChange(Bonnie, onCamera, isDoorDown, playerOnCamera);
			move = false;
		}


		deltaTime = std::time(0);
	}
	//if time passes, and there is no door, then jumpscare
	//but door is back closed then back at


	bool move = doMove(Foxy);
	if (move)
	{
		positionChange(Foxy, onCamera, isDoorDown, playerOnCamera);
	}
	//foxy camera things
	if ((onCamera == 1) && (playerOnCamera))
	{
		onCamTime += time(0) - deltaOnCam;
	}
	else
	{
		deltaOnCam = time(0);
	}
	//Foxy is a special case
}

int* returnPosition()
{
	int* position = new int[4];
	position[0] = Freddy.position;
	position[1] = Bonnie.position;
	position[2] = Chica.position;
	position[3] = Foxy.position;
	return position;
}