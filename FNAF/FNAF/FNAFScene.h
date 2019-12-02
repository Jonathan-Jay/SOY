#pragma once
#include "Animatronic.h"
#include "Game.h"

class FNAF : public Scene
{
public:
	FNAF(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	void Update() override;
};

class MainMenu : public Scene
{
public:
	MainMenu(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	void Update() override;
};

class Set {
public:
	//resets variables
	static void Reset(entt::registry* m_register);
	//position testing function
	static bool positionTesting(int entity, vec3(otherposition), bool isPlayer = false);
	//setup camera set
	static void SetUpSet(int OldCameraChoice, int CameraChoice, bool isAnimatronicPresent[3], int foxyPos, bool buttonPressed);
	//undo camera set
	static void UndoSet(int CameraChoice, bool isAnim[3], int foxyPos);
	//update timer
	static void Update();

private:
	static entt::registry* m_register;
	static bool settingup;
	static bool hasStatic;
	static bool oldIsAnim[3];
	static float wait;
};