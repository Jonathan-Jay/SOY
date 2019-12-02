#include "Game.h"

#include <random>


Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	//Scene names and clear colors
	m_name = "Top-down FNAF";
	m_clearColor = vec4(0.1f, 0.1f, 0.1f, 0.1f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	m_scenes.push_back(new FNAF("Game Scene"));
	m_scenes.push_back(new MainMenu("Main Menu"));

	m_activeScene = m_scenes[1];
	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	m_register = m_activeScene->GetScene();

	Soundfunctions().LoadSound("Menu_Music.mp3");
	Soundfunctions().LoadSound("Fan_Buzzing.mp3");
	Soundfunctions().AdjustVolume("Fan_Buzzing.mp3", 250);
	Soundfunctions().LoadSound("Door_Sound.mp3");
	Soundfunctions().LoadSound("HallLights_On.mp3");
	Soundfunctions().LoadSound("Camera_Switch_Static.mp3");
	Soundfunctions().LoadSound("Foxy_Knock.mp3");
	Soundfunctions().LoadSound("Slow_Laugh.mp3");
	Soundfunctions().LoadSound("Jumpscare.mp3");
	Soundfunctions().LoadSound("Victory_Chimes.mp3");
	Soundfunctions().LoadSound("cheering.mp3");
	Soundfunctions().LoadSound("Window_scare.mp3");

	Set::Reset(m_register);
	Soundfunctions().LoopSound("Menu_Music.mp3");
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();

		//Flips the windows
		m_window->Flip();

		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}

		//if Game is loaded
		if (m_activeScene == m_scenes[0])
		{
			//gameState 0 is first loaded, 1 means game started, 2 means game over, 3 means win
			if (gameState == 1)
			{
				SetScene();
				//Update rendering system
			}
			
			if (gameState == 2)
			{
				//if die, remove camera menu
				if (onCamera)
				{
					onCamera = false;
					change = true;
					SetScene();
				}

				TrackerPos = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
				if (playSound) {
					Soundfunctions().PauseSound("Fan_Buzzing.mp3");
					m_register->get<Transform>(EntityIdentifier::Button(60 + killedYou)).SetPosition(
						TrackerPos + vec3(0.f, 15.f, 1.f));
					wait = 0.f;

					Soundfunctions().PlaySingleSound("JumpScare.mp3");
					playSound = false;
				}

				wait += Timer::deltaTime;

				if (wait >= 5.f) {
					change = false;
					Soundfunctions().LoopSound("Menu_Music.mp3");
					m_activeScene->Unload();
					m_activeScene = m_scenes[1];
					m_activeScene->Unload();
					m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

					m_register = m_activeScene->GetScene();

					Set::Reset(m_register);
				}
			}

			if (gameState == 3)
			{
				//if win, remove camera menu
				if (onCamera)
				{
					onCamera = false;
					change = true;
					SetScene();
				}

				TrackerPos = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
				if (playSound) {
					Soundfunctions().PauseSound("Fan_Buzzing.mp3");
					wait = 0.f;

					Soundfunctions().PlaySingleSound("Victory_Chimes.mp3");
					playSound = false;
				}

				wait += Timer::deltaTime;

				if (wait >= 8.f && wait < 9.f) {
					wait += 1.f;
					Soundfunctions().PlaySingleSound("cheering.mp3");
				}

				if (wait >= 16.f) {
					change = false;
					Soundfunctions().LoopSound("Menu_Music.mp3");
					m_activeScene->Unload();
					m_activeScene = m_scenes[1];
					m_activeScene->Unload();
					m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

					m_register = m_activeScene->GetScene();

					Set::Reset(m_register);
				}
			}
			
			Set::Update();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::Checkbox("Collision", &collision);
		ImGui::Checkbox("Acceleration", &accelerate);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	//Main menu controls
	if (m_activeScene == m_scenes[1])
	{
		MainMenuControls(BackEnd::GetClickEvent());
	}

	//game controls
	if (m_activeScene == m_scenes[0])
	{
		if (m_motion)
			MouseMotion(BackEnd::GetMotionEvent());

		if (m_click)
			MouseClick(BackEnd::GetClickEvent());

		if (m_wheel)
			MouseWheel(BackEnd::GetWheelEvent());

		//Movement control
		MovementMath(EntityIdentifier::MainPlayer());
	}
}

void Game::AcceptInput()
{
	//Just calls all the other input functions 
	KeyboardHold();
	KeyboardDown();
	KeyboardUp();
	
	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::KeyboardHold()
{
	//Keyboard button held
}

void Game::KeyboardDown()
{
	//Keyboard button down
}

void Game::KeyboardUp()
{
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
}

void Game::MovementMath(int mainplayer)
{
	//get vector moving towards TrackerPos
	vec3(CurrentPos) = m_register->get<Transform>(mainplayer).GetPosition();
	vec2(distance) = vec2(TrackerPos.x - CurrentPos.x, TrackerPos.y - CurrentPos.y);

	//to avoid bouncing from plaer when moving
	if (distance.GetMagnitude() > acceleration / 100.f)
	{
		if (!accelerate)	acceleration = 200.f;
		movement = distance.Normalize() * acceleration;
		acceleration += 400 * Timer::deltaTime;
	}
	else	acceleration = 75;	//reset acceleration when stopped

	//change position
	CurrentPos = CurrentPos + vec3(movement.x, movement.y, 0.f) * Timer::deltaTime;

	//rotating the character
	if (movement.x > 0)		m_register->get<Transform>(mainplayer).SetRotationAngleZ(PI - movement.GetAngle(vec2(0.f, 1.f)));
	else if(movement.x < 0)	m_register->get<Transform>(mainplayer).SetRotationAngleZ(PI + movement.GetAngle(vec2(0.f, 1.f)));
	else if(movement.y < 0)	m_register->get<Transform>(mainplayer).SetRotationAngleZ(0);
	else m_register->get<Transform>(mainplayer).SetRotationAngleZ(PI);

	//option to stop wall collision
	if (collision)
	{
		if (CurrentPos.x > 37.5)	{ CurrentPos.x = 37.5;		acceleration = 75; }
		if (CurrentPos.x < -37.5)	{ CurrentPos.x = -37.5;		acceleration = 75; }
		if (CurrentPos.y > -39)		{ CurrentPos.y = -39;		acceleration = 75; }
		if (CurrentPos.y < -93)		{ CurrentPos.y = -93;		acceleration = 75; }
	}

	//change position
	m_register->get<Transform>(mainplayer).SetPosition(CurrentPos);

	//Wall button testing, check both sides (0 for left, 1 for right)
	for (int x(1); x <= 2; x++)
	{
		//button being active or not is stored in bool array isButtonPressed
		//0 and 1 are lights (left and right)
		//2 and 3 are doors (left and right)
		
		//testing for light button being pressed
		if (Set::positionTesting(EntityIdentifier::Button(10 * x), CurrentPos, true))
		{
			isButtonPressed[x - 1] = true;
			if (notTouchingButton[x - 1])
			{
				if (power > 1)
					Soundfunctions().LoopSound("HallLights_On.mp3");
				notTouchingButton[x - 1] = false;
			}

			if (animatronicAtWindow[x - 1])
			{
				if (animatronicAtWindow[x + 1]) {
					Soundfunctions().PlaySingleSound("Window_scare.mp3");
					animatronicAtWindow[x + 1] = false;
				}
			}
		}
		else {
			isButtonPressed[x - 1] = false;
			if (!notTouchingButton[x - 1])
			{
				if (power > 1)
					Soundfunctions().PauseSound("HallLights_On.mp3");
				notTouchingButton[x - 1] = true;
			}
		}

		//testing for door button being pressed
		if (Set::positionTesting(EntityIdentifier::Button(10 * x + 20), CurrentPos, true))
		{
			//only activate after player gets off button, stored in notTouchingButton (0 for left, 1 for right)
			if (notTouchingButton[x + 1])
			{
				if (power >= 1)
					Soundfunctions().PlaySingleSound("Door_Sound.mp3");
				isButtonPressed[x + 1] = !isButtonPressed[x + 1];	//swap button state
				notTouchingButton[x + 1] = false;
			}
		}
		else notTouchingButton[x + 1] = true;	//set notTouchingButton back to true once player leaves
	}

	for (int x(1); x <= 4; x++)
	{
		vec3 direction = m_register->get<Transform>(EntityIdentifier::Button(60 + x)).GetPosition() - CurrentPos;
		float angle = atan2f(direction.y, direction.x);
		m_register->get<Transform>(EntityIdentifier::Button(60 + x)).SetRotationAngleZ(angle);
	}

	//reset movement vector
	movement = vec2(0.f, 0.f);
}

void Game::SetScene()
{
	//sum is power usage, using true = 1 and false = 0 to calculate sum (3 is max)
	int sum = onCamera;
	for (int x(0); x < 4; x++)
	{
		sum += isButtonPressed[x];
	}
	//reduce power depending on usage
	if (power >= 1)
	{
		power -= (sum * 0.2f + 0.2f) * Timer::deltaTime;
	}
	else
	{
		onCamera = false;
		change = true;
		sum = 0;
		for (int x(0); x < 4; x++)
		{
			isButtonPressed[x] = false;
		}
		m_register->get<AnimationController>(EntityIdentifier::Button(49)).SetActiveAnim(1);
	}
	//clock
	currenttime += Timer::deltaTime;
	if (currenttime >= 271)
	{
		gameState = 3;
		playSound = true;
	}

	if (power < 1) {
		power = 0;
		Difficulty(40, 0);
	}

	//runing whether to move the characters or not
	Animatronic::changePosition(CameraChoice, currenttime, isButtonPressed, onCamera, power);

	int* AnimatronicPos = returnPosition();

	//changing display for power, and time
	m_register->get<AnimationController>(EntityIdentifier::Button(0)).SetActiveAnim(floor(currenttime / 45));
	m_register->get<AnimationController>(EntityIdentifier::Button(21)).SetActiveAnim(floor(power / 10));
	m_register->get<AnimationController>(EntityIdentifier::Button(31)).SetActiveAnim(floor(power) - (floor(power / 10) * 10));
	m_register->get<AnimationController>(EntityIdentifier::Button(41)).SetActiveAnim(sum);

	int foxyPos = 0;
	bool isAnimatronicInRoom[3] = {};
	//Animatronics according to number in isAnimatronicInRoom
	//0 is freddy
	//1 is chica
	//2 is bonnie
	//3 is foxy
	if (CameraChoice == AnimatronicPos[0])
	{
		isAnimatronicInRoom[0] = true;
		//check if animatronic changed position since last update
		if (oldAnimPos[0] != AnimatronicPos[0])
		{
			change = true;
			oldAnimPos[0] = AnimatronicPos[0];
		}
	}
	else if (oldAnimPos[0] == CameraChoice)
	{	//check if animatronic left the room
		change = true;
		oldAnimPos[0] = AnimatronicPos[0];
	}
	if (CameraChoice == AnimatronicPos[1])
	{
		isAnimatronicInRoom[1] = true;
		if (oldAnimPos[1] != AnimatronicPos[1])
		{
			change = true;
			oldAnimPos[1] = AnimatronicPos[1];
		}
	}
	else if (oldAnimPos[1] == CameraChoice)
	{
		change = true;
		oldAnimPos[1] = AnimatronicPos[1];
	}
	if (CameraChoice == AnimatronicPos[2])
	{
		isAnimatronicInRoom[2] = true;
		if (oldAnimPos[2] != AnimatronicPos[2])
		{
			change = true;
			oldAnimPos[2] = AnimatronicPos[2];
		}
	}
	else if (oldAnimPos[2] == CameraChoice)
	{
		change = true;
		oldAnimPos[2] = AnimatronicPos[2];
	}
	//checking if on camera 1 (foxy's room) then taking foxy's position
	if (CameraChoice == 1)	foxyPos = AnimatronicPos[3];

	if (!onCamera)
	{
		//if Bonnie is in the left hall
		if (AnimatronicPos[1] == 9) {
			m_register->get<Transform>(EntityIdentifier::Button(62)).SetPositionY(-66);
			animatronicAtWindow[0] = true;
		}
		else {
			m_register->get<Transform>(EntityIdentifier::Button(62)).SetPositionY(-200);
			animatronicAtWindow[0] = false;
			animatronicAtWindow[2] = true;
		}
		//if Chica is in the right hall
		if (AnimatronicPos[2] == 10) {
			m_register->get<Transform>(EntityIdentifier::Button(63)).SetPositionY(-66);
			animatronicAtWindow[1] = true;
		}
		else {
			m_register->get<Transform>(EntityIdentifier::Button(63)).SetPositionY(-200);
			animatronicAtWindow[1] = false;
			animatronicAtWindow[3] = true;
		}
	}

	for (int x(0); x < 4; x++)
	{
		if (AnimatronicPos[x] == 11)
		{
			killedYou = x + 1;
			gameState = 2;
			playSound = true;
		}
	}

	//change means update scene, so it doesn't update every frame
	if (onCamera && change)
	{
		Set::SetUpSet(OldCameraChoice, CameraChoice, isAnimatronicInRoom, foxyPos, buttonPressed);
	}
	else if (change)
	{
		Set::UndoSet(CameraChoice, isAnimatronicInRoom, foxyPos);
	}

	//changes animation for buttons 0 for left, 1 for right
	for (int x(0); x < 2; x++)
	{
		//change animation for light buttons
		m_register->get<AnimationController>(EntityIdentifier::Button(10 * (x + 1) )).SetActiveAnim(isButtonPressed[x]);
		
		//blinking timer for lights, animation 0 is off if doesn't reach timer, sets to light status (true = 1, false = 0)
		if (counter > wait)
		{
			m_register->get<AnimationController>(EntityIdentifier::Button(19 + 10 * x)).SetActiveAnim(0);
			//reset counter and wait time
			if (x == 1)
			{
				counter = 0;
				wait = rand() % 5 / 10.f + 0.1f;
			}
		}
		else m_register->get<AnimationController>(EntityIdentifier::Button(19 + 10 * x)).SetActiveAnim(isButtonPressed[x]);
		//sets both doors and door buttons
		m_register->get<AnimationController>(EntityIdentifier::Button(30 + 10 * x)).SetActiveAnim(isButtonPressed[x + 2]);
		m_register->get<AnimationController>(EntityIdentifier::Button(50 + 10 * x)).SetActiveAnim(isButtonPressed[x + 2]);
		
	}
	//increase counter for light blink
	counter += Timer::deltaTime;

	//reset values
	change = false;
	buttonPressed = false;
}

void Game::MainMenuControls(SDL_MouseButtonEvent evnt)
{
	float windowWidth = BackEnd::GetWindowWidth();
	float windowHeight = BackEnd::GetWindowHeight();
	
	//Contols for main menu
	for (int x(1); x <= 5; x++)
	{
		//buttons glitch change happens 1% of the time
		if (rand() % 100 >= 99)
		{
			m_register->get<AnimationController>(EntityIdentifier::Button(x)).SetActiveAnim(1);
		}
		else	m_register->get<AnimationController>(EntityIdentifier::Button(x)).SetActiveAnim(0);
	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		vec3(click) = vec3(
			evnt.x / windowHeight * 200.f - 100.f * windowWidth / windowHeight,
			-evnt.y / windowHeight * 200.f + 100.f,
			0.f);
		for (int x(1); x <= 5; x++)
		{
			//check if bight button was pressed
			if (Set::positionTesting(EntityIdentifier::Button(x), click)) {
				//brings loading screen into frame
				m_register->get<Transform>(EntityIdentifier::Button(0)).SetPositionY(0);
				printf("Night %i\n", x);
				Soundfunctions().PlaySingleSound("Camera_Switch_Static.mp3");
				//setting up difficulty according to night
				switch (x)
				{
				default:
				case 1:
					initializeAnimatronics(5, 1, 5); //difficulty is the overload out of 100%, nightNumber, then followed by Freddy's difficulty
					break;
				case 2:
					initializeAnimatronics(10, 2, 10);
					break;
				case 3:
					initializeAnimatronics(15, 3, 15);
					break;
				case 4:
					initializeAnimatronics(20, 4, 20);
					break;
				case 5:
					initializeAnimatronics(30, 5, 30);
					break;
				}
				change = true;
				wait = 0;
			}

			//teleport all buttons out of scene after selection to prevent repeat clicking
			if (change)
			{
				m_register->get<Transform>(EntityIdentifier::Button(x)).SetPositionY(200);
			}
		}
	}
	
	//if a button was selected
	if (change)
	{
		//display loading screen
		wait += Timer::deltaTime;
		if (wait >= 2.f)
		{
			//change scene
			m_activeScene = m_scenes[0];

			m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

			m_register = m_activeScene->GetScene();

			//place reset animatronic position here
			//initial positions would be 3, 3, 3, 1

			//reset set class function variables and send register and reset variables
			Set::Reset(m_register);
			Soundfunctions().PauseSound("Menu_Music.mp3");
			Soundfunctions().LoopSound("Fan_Buzzing.mp3");
			currenttime = 0;
			power = 100;
			gameState = 0;
			TrackerPos = vec3(0.f, -50.f, 0.f);
			CameraChoice, OldCameraChoice = 3;
			for (int x(0); x < 4; x++)
			{
				isButtonPressed[x] = false;
				if (x < 3)
				{
					oldAnimPos[x] = 3;
				}
			}
		}
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	vec3(playerPos) = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

	//check if player is in front of desk
	if (gameState == 1 && power > 1 && playerPos.y >= -41 && playerPos.x < 20 && playerPos.x > -20)
	{
		//display bar (set animation to 1)
		m_register->get<AnimationController>(EntityIdentifier::Button(39)).SetActiveAnim(1);

		//check if mouse was moved downwards over 10 pixels bellow bottom of tab and not currently on Camera
		if (!onCamera && oldposition.y + 10 <= evnt.y && evnt.y >= BackEnd::GetWindowHeight() - 4)
		{
			printf("Camera On!\n");
			Soundfunctions().PlaySingleSound("Camera_Switch_Static.mp3");
			//sets a bunch of variables to update
			TrackerPos = playerPos;
			acceleration = 75;
			change = true;
			buttonPressed = true;
			onCamera = true;
			playSound= false;
		}
	}
	else	m_register->get<AnimationController>(EntityIdentifier::Button(39)).SetActiveAnim(0);	//hide bar

	//store last mouse position
	oldposition = vec2(float(evnt.x), float(evnt.y));
	
	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	float windowWidth = BackEnd::GetWindowWidth();
	float windowHeight = BackEnd::GetWindowHeight();

	if (gameState <= 1 && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		vec3(click) = vec3(
			evnt.x / windowHeight * 200.f - 100.f * windowWidth / windowHeight,
			-evnt.y / windowHeight * 200.f + 100.f,
			0.f);

		//if not on camera change TrackerPos so that player moves towards mouse click
		if (!onCamera)
		{
			TrackerPos = click;
			//if mouse pressed on door button, reset notTouchingButton, making the door switch
			if (Set::positionTesting(EntityIdentifier::Button(30), click, true))	notTouchingButton[2] = true;
			if (Set::positionTesting(EntityIdentifier::Button(40), click, true))	notTouchingButton[3] = true;
		}
		else
		{
			for (int x(1); x <= 8; x++)
			{
				//if on camera and pressing on camera button different from current one
				if (CameraChoice != x && Set::positionTesting(EntityIdentifier::Button(x), click))
				{
					printf("Camera %i selected\n", x);
					Soundfunctions().PlaySingleSound("Camera_Switch_Static.mp3");
					//sets a bunch of variables
					OldCameraChoice = CameraChoice;
					change = true;
					buttonPressed = true;
					CameraChoice = x;
				}
			}
		}

		//if player clickes screen, start clock, this is to avoid clock starting during boot up
		if (gameState == 0)	gameState = 1;
	}

	//if player right clicks while on camera
	if (onCamera && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		printf("Camera Off!\n");
		onCamera = false;
		change = true;
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}

	//Resets the enabled flag
	m_wheel = false;
}
