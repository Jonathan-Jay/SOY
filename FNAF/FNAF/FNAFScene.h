#pragma once
#include "Animatronic.h"
#include "Game.h"

class FNAF : public Scene
{
public:
	FNAF(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
};

class Set {
public:
	static void GetRegister(entt::registry* m_register);
	static bool positionTesting(int entity, vec3(otherposition), bool isPlayer = false);
	static void SetUpSet(int OldCameraChoice, int CameraChoice, bool isAnimatronicPresent[4]);
	static void UndoSet(int CameraChoice);

private:
	static entt::registry* m_register;
	static bool settingup;
};