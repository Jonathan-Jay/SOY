#ifndef __GAME_H__
#define __GAME_H__

#include "BackEnd.h"
#include "FNAFScene.h"

//Our main class for running our game
class Game
{
public:
	//Empty constructor
	Game() { };
	//Deconstructor for game
	//*Unloads window
	~Game();

	//Initiaiizes game
	//*Seeds random
	//*Initializes SDL
	//*Creates Window
	//*Initializes GLEW
	//*Create Main Camera Entity
	//*Creates all other entities and adds them to register
	void InitGame();

	//Runs the game
	//*While window is open
	//*Clear window
	//*Update 
	//*Draw
	//*Poll events
	//*Flip window
	//*Accept input
	bool Run();
	
	//Updates the game
	//*Update timer
	//*Update the rendering system
	//*Update the animation system
	void Update();

	//Runs the GUI
	//*Uses ImGUI for this
	void GUI();

	//Check events
	//*Checks the results of the events that have been polled
	void CheckEvents();

	/*Input Functions*/
	void AcceptInput();
	void KeyboardHold();
	void KeyboardDown();
	void KeyboardUp();

	void MovementMath(int mainplayer);
	void SetScene();

	void MainMenuControls(SDL_MouseButtonEvent evnt);

	//Mouse input
	void MouseMotion(SDL_MouseMotionEvent evnt);
	void MouseClick(SDL_MouseButtonEvent evnt);
	void MouseWheel(SDL_MouseWheelEvent evnt);
private:
	//The window
	Window *m_window = nullptr;

	//Scene name
	std::string m_name;
	//Clear color for when we clear the window
	vec4 m_clearColor;
	
	//The main register for our ECS
	entt::registry* m_register;

	//Scenes
	Scene* m_activeScene;
	std::vector<Scene*> m_scenes;
	
	//Imgui stuff
	bool m_guiActive = false;

	//Hooks for events
	bool m_close = false;
	bool m_motion = false;
	bool m_click = false;
	bool m_wheel = false;
	
	//our stuff
	bool onCamera = false;
	bool change = false;
	bool buttonPressed = false;
	bool leftButton[2] = {};
	bool isButtonPressed[4] = {};

	int CameraChoice = 3;
	int OldCameraChoice = 3;
	int oldAnimPos[3] = {3, 3, 3};
	float counter = 0;
	float wait = 5;
	vec2(movement) = vec2(0.f, 0.f);
	vec2(oldposition) = vec2(0.f, 0.f);

	vec3(TrackerPos) = vec3(0.f, -50.f, 0.f);

	int tempAnimPos[4] = {3, 3, 3, 1};
};



#endif // !__GAME_H__

