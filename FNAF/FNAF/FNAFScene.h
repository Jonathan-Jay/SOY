#pragma once
#include "Animatronic.h"
#include "Game.h"
#include "AudioManager.h"

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
	static void GetRegister(entt::registry* m_register);
	static bool positionTesting(int entity, vec3(otherposition), bool isPlayer = false);
	static void SetUpSet(int OldCameraChoice, int CameraChoice, bool isAnimatronicPresent[3], 
		int foxyPos, bool buttonPressed, bool flipped);
	static void UndoSet(int CameraChoice, bool isAnim[3], int foxyPos);
	static void Update();

private:
	static entt::registry* m_register;
	static bool settingup;
	static bool hasStatic;
	static bool oldIsAnim[3];
	static float wait;
};