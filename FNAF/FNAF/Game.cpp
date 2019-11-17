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
	m_name = "Main Scene";
	m_clearColor = vec4(0.1f, 0.1f, 0.1f, 0.1f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	m_scenes.push_back(new FNAF("Main Scene"));

	m_activeScene = m_scenes[0];

	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	//*m_activeScene = File::LoadJSON("Main Scene.json");			//if we want to load a JSON

	m_register = m_activeScene->GetScene();

	Set::GetRegister(m_register);
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

		SetScene();
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);
	//characterMove();
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	int mainplayer = EntityIdentifier::MainPlayer();
	
	//Just calls all the other input functions 
	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	MovementMath(mainplayer);
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
	int tracker = EntityIdentifier::Button(0);
	vec3(CurrentPos) = m_register->get<Transform>(mainplayer).GetPosition();
	vec3(TrackerPos) = m_register->get<Transform>(tracker).GetPosition();
	vec2(distance) = vec2(TrackerPos.x - CurrentPos.x, TrackerPos.y - CurrentPos.y);

	if (distance.GetMagnitude() > 0.5f)	movement = distance.Normalize() * 100.f;
	
	CurrentPos = CurrentPos + vec3(movement.x, movement.y, 0.f) * Timer::deltaTime;

	if (movement.x > 0)		m_register->get<Transform>(mainplayer).SetRotationAngleZ(PI - movement.GetAngle(vec2(0.f, 1.f)));
	else if(movement.x < 0)	m_register->get<Transform>(mainplayer).SetRotationAngleZ(PI + movement.GetAngle(vec2(0.f, 1.f)));
	else if(movement.y < 0)	m_register->get<Transform>(mainplayer).SetRotationAngleZ(0);
	else m_register->get<Transform>(mainplayer).SetRotationAngleZ(PI);

	if (CurrentPos.x > 43)	CurrentPos.x = 43;
	if (CurrentPos.x < -43)	CurrentPos.x = -43;
	if (CurrentPos.y > -40)	CurrentPos.y = -40;
	if (CurrentPos.y < -93)	CurrentPos.y = -93;

	m_register->get<Transform>(mainplayer).SetPosition(CurrentPos);
	movement = vec2(0.f, 0.f);
}

void Game::SetScene()
{
	if (onCamera && change) {
		Set::SetUpSet(OldCameraChoice, CameraChoice);
	}
	else if (change) {
		Set::UndoSet(CameraChoice);
	}
	change = false;
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

	if (oldposition.y - 10 <= evnt.y && evnt.y >= BackEnd::GetWindowHeight() - 4 &&
		playerPos.y >= -41 && playerPos.x < 20 && playerPos.x > -20 && !onCamera)
	{
		printf("Camera On!\n");
		m_register->get<Transform>(EntityIdentifier::Button(0)).SetPosition(playerPos);
		change = true;
		onCamera = true;
	}

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
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		vec3(click) = vec3(
			evnt.x / windowHeight * 200.f - 100.f * windowWidth / windowHeight,
			-evnt.y / windowHeight * 200.f + 100.f,
			0.f);
		if (!onCamera)	m_register->get<Transform>(EntityIdentifier::Button(0)).SetPosition(click);

		for (int x(1); x <= 8; x++) {
			if (Set::positionTesting(EntityIdentifier::Button(x), click)) {
				printf("%i\n", x);
				OldCameraChoice = CameraChoice;
				CameraChoice = x;
				change = true;
			}
		}

	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
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
