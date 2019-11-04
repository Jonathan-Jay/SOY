#pragma once
#include "Scene.h"

class FNAF : public Scene
{
public:
	FNAF(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
};