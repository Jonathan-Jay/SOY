#include "FNAFScene.h"

entt::registry* Set::m_register = nullptr;
bool Set::settingup = true;
bool Set::hasStatic = false;
bool Set::oldIsAnim[3] = {};
float Set::wait = 0;

FNAF::FNAF(std::string name)
	: Scene(name)
{
}

void FNAF::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

#pragma region camera
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Camera>(entity);

		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Camera");
		ECS::SetIsMainCamera(entity, true);
	}
#pragma endregion

#pragma region office
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string filename = "room.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 200, 200);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -50.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "room");
	}
#pragma endregion

#pragma region player
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string filename = "player.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 25, 14);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -50.f, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "player");
		ECS::SetIsMainPlayer(entity, true);
	}
#pragma endregion

	//Button 0
#pragma region Time
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string filename = "time.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(filename);

		for (int x(0); x < 7; x++) {
			animController.AddAnimation(Animation());
			auto& anim = animController.GetAnimation(x);
			anim.AddFrame(vec2(1,24 * (x + 1)), vec2(47, x * 24));
			anim.SetRepeating(false);
			anim.SetSecPerFrame(0.1f);
		}

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 33, 15, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(79.f, 90.f, 45.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "time");
		ECS::SetIsButton(entity, true, 0);
	}
#pragma endregion
	
	//Button 21, 31, 41
#pragma region Power
	for (int x(1); x < 4; x++)
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		int temp(0);
		std::string filename = "power";
		switch (x) {
		case 1:
			filename += "counter.png";
			temp = 10;
			break;
		case 2:
			filename += "digit.png";
			temp = 10;
			break;
		case 3:
			filename += "bar.png";
			temp = 4;
			break;
		default:	break;
		}
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(filename);

		for (int y(0); y < temp; y++) {
			animController.AddAnimation(Animation());
			auto& anim = animController.GetAnimation(y);
			anim.AddFrame(vec2(1, 24 * (y + 1)), vec2(127, y * 24));
			anim.SetRepeating(false);
			anim.SetSecPerFrame(0.1f);
		}

		if (x < 3)
			animController.SetActiveAnim(9);
		else	animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 93, 15, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-50.f, 90.f, 45.f + x));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "power UI part " + std::to_string(x));
		ECS::SetIsButton(entity, true, 11 + x * 10);
	}
#pragma endregion
	
	//Button 9
#pragma region map
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string filename = "map.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 92, 81);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, 500.f, 40.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "map");
		ECS::SetIsButton(entity, true, 9);
	}
#pragma endregion
	
	//Button 39
#pragma region bar
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string filename = "bar.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(filename);

		animController.AddAnimation(Animation());
		animController.AddAnimation(Animation());

		animController.SetActiveAnim(0);

		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(0, 40), vec2(150, 22));
		anim.SetRepeating(false);
		anim.SetSecPerFrame(0.1f);

		auto& anim2 = animController.GetAnimation(1);
		anim2.AddFrame(vec2(0, 20), vec2(150, 0));
		anim2.SetRepeating(false);
		anim2.SetSecPerFrame(0.1f);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 75, 10, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -90.f, 10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "bar");
		ECS::SetIsButton(entity, true, 39);
	}
#pragma endregion
	
	//Button 49
#pragma region screen cover
	{
		srand(time(0));
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string filename = "cover.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(filename);

		animController.AddAnimation(Animation());
		animController.AddAnimation(Animation());

		animController.SetActiveAnim(0);

		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(1, 1), vec2(1, 0));

		anim.SetRepeating(false);
		anim.SetSecPerFrame(0.1f);

		auto& anim2 = animController.GetAnimation(1);
		anim2.AddFrame(vec2(1, 1), vec2(1, 0));
		for (int x(0); x < 18; x++) {
			if (rand() % 10 < 5)	anim2.AddFrame(vec2(0, 1), vec2(0, 0));
			else	anim2.AddFrame(vec2(1, 1), vec2(1, 0));
		}
		anim2.AddFrame(vec2(0, 1), vec2(0, 0));

		anim2.SetRepeating(false);
		anim2.SetSecPerFrame(0.1f);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 200, 200, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 50.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		
		ECS::SetUpIdentifier(entity, bitHolder, "Screen cover");
		ECS::SetIsButton(entity, true, 49);
	}
#pragma endregion

	//so that we can mass spawn without filling the cpp
	for (int x(1); x <= 8; x++) {
		
	//Button 10 * 1-6, 19, 29
#pragma region wall buttons doors & lights
		if (x <= 6)		//wall buttons and doors (10 - 60)
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<AnimationController>(entity);

			std::string filename = "door";
			if (x <= 2)			filename = "light button.png";
			else if (x <= 4)	filename += " button.png";
			else				filename += ".png";

			auto& animController = ECS::GetComponent<AnimationController>(entity);
			animController.InitUVs(filename);

			animController.AddAnimation(Animation());
			animController.AddAnimation(Animation());

			animController.SetActiveAnim(0);

			auto& anim = animController.GetAnimation(0);
			if (x <= 4)		anim.AddFrame(vec2(0, 2), vec2(0, 0));
			else			anim.AddFrame(vec2(22, 29), vec2(42, 0));

			anim.SetRepeating(false);
			anim.SetSecPerFrame(0.1f);

			auto& anim2 = animController.GetAnimation(1);
			if (x <= 4)		anim2.AddFrame(vec2(1, 2), vec2(1, 0));
			else			anim2.AddFrame(vec2(0, 29), vec2(20, 0));

			anim2.SetRepeating(false);
			anim2.SetSecPerFrame(0.1f);

			if (x <= 4)
				ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 4, 8, true, &animController);
			else
				ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 21, 29, true, &animController);


			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();

			switch (x) {
			case 1:		ECS::SetUpIdentifier(entity, bitHolder, "light button left");
						ECS::GetComponent<Transform>(entity).SetPosition(vec3(-40.5f, -45.f, 0.f));
						break;
			case 2:		ECS::SetUpIdentifier(entity, bitHolder, "light button right");
						ECS::GetComponent<Transform>(entity).SetPosition(vec3(40.5f, -45.f, 0.f));
						break;
			case 3:		ECS::SetUpIdentifier(entity, bitHolder, "door button left");
						ECS::GetComponent<Transform>(entity).SetPosition(vec3(-40.5f, -91.f, 0.f));
						break;
			case 4:		ECS::SetUpIdentifier(entity, bitHolder, "door button right");
						ECS::GetComponent<Transform>(entity).SetPosition(vec3(40.5f, -91.f, 0.f));
						break;
			case 5:		ECS::SetUpIdentifier(entity, bitHolder, "door left");
						ECS::GetComponent<Transform>(entity).SetPosition(vec3(-53.2f, -67.8f, 0.f));
						break;
			case 6:		ECS::SetUpIdentifier(entity, bitHolder, "door right");
						ECS::GetComponent<Transform>(entity).SetPosition(vec3(53.2f, -67.8f, 0.f));
						break;
			default:	break;
			}

			ECS::SetIsButton(entity, true, 10 * x);
		}
		else	//lights
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<AnimationController>(entity);

			std::string filename = "light.png";

			auto& animController = ECS::GetComponent<AnimationController>(entity);
			animController.InitUVs(filename);

			animController.AddAnimation(Animation());
			animController.AddAnimation(Animation());

			animController.SetActiveAnim(0);

			auto& anim = animController.GetAnimation(0);
			anim.AddFrame(vec2(0, 1), vec2(0, 0));

			anim.SetRepeating(false);
			anim.SetSecPerFrame(0.1f);

			auto& anim2 = animController.GetAnimation(1);
			anim2.AddFrame(vec2(1, 1), vec2(1, 0));

			anim2.SetRepeating(false);
			anim2.SetSecPerFrame(0.1f);

			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 37, 200, true, &animController);
			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
			if (x == 7) {
				ECS::SetUpIdentifier(entity, bitHolder, "light left");
				ECS::GetComponent<Transform>(entity).SetPosition(vec3(-81.5f, 0.f, 0.f));
				ECS::SetIsButton(entity, true, 19);
			}
			else {
				ECS::SetUpIdentifier(entity, bitHolder, "light right");
				ECS::GetComponent<Transform>(entity).SetPosition(vec3(82.f, 0.f, 0.f));
				ECS::SetIsButton(entity, true, 29);
			}
		}
#pragma endregion
		
	//Button 1-8
#pragma region camera buttons
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<AnimationController>(entity);

			std::string filename = "buttons.png";
			auto& animController = ECS::GetComponent<AnimationController>(entity);
			animController.InitUVs(filename);

			animController.AddAnimation(Animation());
			animController.AddAnimation(Animation());

			animController.SetActiveAnim(0);

			auto& anim = animController.GetAnimation(0);
			anim.AddFrame(vec2(2.f, (22.f * x) - 1.f), vec2(46.f, 22.f * (x - 1) + 2.f));

			anim.SetRepeating(false);
			anim.SetSecPerFrame(0.1f);

			auto& anim2 = animController.GetAnimation(1);
			anim2.AddFrame(vec2(48.f, (22.f * x) - 1.f), vec2(91.f, 22.f * (x - 1) + 2.f));
			anim2.AddFrame(vec2(48.f, (22.f * x) - 1.f), vec2(91.f, 22.f * (x - 1) + 2.f));
			anim2.AddFrame(vec2(48.f, (22.f * x) - 1.f), vec2(91.f, 22.f * (x - 1) + 2.f));
			anim2.AddFrame(vec2(94.f, (22.f * x) - 1.f), vec2(137.f, 22.f * (x - 1) + 2.f));
			anim2.AddFrame(vec2(140.f, (22.f * x) - 1.f), vec2(183.f, 22.f * (x - 1) + 2.f));

			anim2.SetRepeating(false);
			anim2.SetSecPerFrame(0.2f);

			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 17, 8, true, &animController);

			switch (x) {
			case 1:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(23.f, 461.5f, 50.f));	break;
			case 2:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(54.f, 464.f, 50.f));	break;
			case 3:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(43.f, 485.5f, 50.f));	break;
			case 4:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(87.5f, 460.5f, 50.f));	break;
			case 5:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(29.f, 445.f, 50.f));	break;
			case 6:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(74.5f, 414.f, 50.f));	break;
			case 7:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(87.8f, 423.4f, 50.f));	break;
			case 8:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(29.5f, 475.f, 50.f));	break;
			default: break;
			}

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit()
				| EntityIdentifier::AnimationBit();
			ECS::SetUpIdentifier(entity, bitHolder, "button " + std::to_string(x));
			ECS::SetIsButton(entity, true, x);
		}
#pragma endregion
		
	//Button 11-18
#pragma region camera rooms
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			std::string filename = "/rooms/" + std::to_string(x) + ".png";
			
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 240, 200);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 500.f, 25.f));

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "room " + std::to_string(x));
			ECS::SetIsButton(entity, true, x + 10);
		}
#pragma endregion
		
	//Button 23
#pragma region Freddy
		if (x == 3)
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			std::string filename = "/rooms/freddy/" + std::to_string(x) + ".png";
			
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 240, 200);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 500.f, 30.f));

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "freddy room " + std::to_string(x));
			ECS::SetIsButton(entity, true, x + 20);
		}
#pragma endregion
	
	//Button 32, 33, 34, 35, 38
#pragma region Bonnie
		if ((x >= 2 && x <= 5) || x == 8)
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			std::string filename = "/rooms/bonnie/" + std::to_string(x) + ".png";
			
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 240, 200);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 500.f, 31.f));

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "bonnie room " + std::to_string(x));
			ECS::SetIsButton(entity, true, x + 30);
		}
#pragma endregion
	
	//Button 42, 43, 47, 48
#pragma region Chica
		if ((x >= 2 && x <= 3) || (x >= 7 && x <= 8))
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			std::string filename = "/rooms/chica/" + std::to_string(x) + ".png";
			
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 240, 200);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 500.f, 30.f));

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "chica room " + std::to_string(x));
			ECS::SetIsButton(entity, true, x + 40);
		}
#pragma endregion
	
	//Button 51-55
#pragma region Foxy
		if (x < 5)
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			std::string filename = "/rooms/foxy/" + std::to_string(x) + ".png";
			
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 240, 200);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 500.f, 30.f));

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "foxy room " + std::to_string(x));
			ECS::SetIsButton(entity, true, x + 50);
		}
#pragma endregion
		
	}

}

void FNAF::Update() { }

bool Set::positionTesting(int entity, vec3(otherposition), bool isPlayer)
{
	vec3(Pos) = otherposition - m_register->get<Transform>(entity).GetPosition();
	
	//isPlayer increase hitbox of buttons
	//position testing takes sprite size and checks for collision with other position
	if (isPlayer) {
		if (Pos.x <= 5 + m_register->get<Sprite>(entity).GetWidth() / 2.f &&
			Pos.x >= -(5 + m_register->get<Sprite>(entity).GetWidth() / 2.f) &&
			Pos.y <= 3 + m_register->get<Sprite>(entity).GetHeight() / 2.f &&
			Pos.y >= -(3 + m_register->get<Sprite>(entity).GetHeight() / 2.f) )
		{
			return true;
		}
	}
	else if (Pos.x <= m_register->get<Sprite>(entity).GetWidth() / 2.f &&
			Pos.x >= -m_register->get<Sprite>(entity).GetWidth() / 2.f &&
			Pos.y <= m_register->get<Sprite>(entity).GetHeight() / 2.f &&
			Pos.y >= -m_register->get<Sprite>(entity).GetHeight() / 2.f)
	{
		return true;
	}
	
	return false;
}

void Set::SetUpSet(int OldCameraChoice, int CameraChoice, bool isAnim[3], int foxyPos, bool buttonPressed)
{
	//sets static time and makes hasStatic true, making static reset
	wait = 0.25f;
	if (!hasStatic)	hasStatic = true;

	//button reseting
	if (buttonPressed) {
		//resets animations for camera choice and last amera choice
		auto& temp = m_register->get<AnimationController>(EntityIdentifier::Button(OldCameraChoice));
		temp.SetActiveAnim(0);
		temp.GetAnimation(1).Reset();
		m_register->get<AnimationController>(EntityIdentifier::Button(CameraChoice)).SetActiveAnim(1);

		//Scene organisation here (CameraChoice is current, OldCameraChoice is previous), add 10 for rooms
		m_register->get<Transform>(EntityIdentifier::Button(OldCameraChoice + 10)).SetPosition(vec3(0, 500, 25));
		m_register->get<Transform>(EntityIdentifier::Button(CameraChoice + 10)).SetPosition(vec3(0, 0, 25));
	}

	//if on camera 1 aka foxy's room
	//foxy is in rooms 51 - 54
	if (OldCameraChoice == 1) {
		for (int x(1); x <= 5; x++) {
			m_register->get<Transform>(EntityIdentifier::Button(50 + x)).SetPosition(vec3(0, 500, 30));
		}
	}
	if (foxyPos > 0 && foxyPos < 5) {
		m_register->get<Transform>(EntityIdentifier::Button(50 + foxyPos)).SetPosition(vec3(0, 0, 30));
	}

	//Animatronics are numbered 20 - 40 + room number, x is a multiplier
	//0 is for fred
	//1 is for bon
	//2 is for goose
	for (int x(0); x < 3; x++) {
		//remove old animatronics unless it was from camera opening or a new button wasn't pressed
		if (oldIsAnim[x] && buttonPressed && !settingup) {
			m_register->get<Transform>(EntityIdentifier::Button(OldCameraChoice + 10 * (x + 2))).SetPosition(vec3(0, 500, 30));
		}

		//if button wasn't pressed and animatronics have left scene, remove them
		if (oldIsAnim[x] != isAnim[x] && !buttonPressed) {
			m_register->get<Transform>(EntityIdentifier::Button(CameraChoice + 10 * (x + 2))).SetPosition(vec3(0, 500, 30));
		}

		//if animatronic should be on scene
		if (isAnim[x]) {
			m_register->get<Transform>(EntityIdentifier::Button(CameraChoice + 10 * (x + 2))).SetPosition(vec3(0, 0, 30));
		}
		
		//reset oldIsAnim
		oldIsAnim[x] = isAnim[x];
	}
	//map
	m_register->get<Transform>(EntityIdentifier::Button(9)).SetPosition(vec3(50, -50, 40.f));

	//setting up camera buttons only when camera opens
	if (settingup) {
		for (int x(1); x <= 8; x++) {
			vec3 temp = m_register->get<Transform>(EntityIdentifier::Button(x)).GetPosition();
			m_register->get<Transform>(EntityIdentifier::Button(x)).SetPosition(vec3(temp.x, temp.y - 500, 50));
		}
		settingup = false;
	}
}

void Set::UndoSet(int CameraChoice, bool isAnim[3], int foxyPos)
{
	//remove map, buttons and animatronic once
	if (!settingup) {
		for (int x(1); x <= 8; x++) {
			vec3 temp = m_register->get<Transform>(EntityIdentifier::Button(x)).GetPosition();
			m_register->get<Transform>(EntityIdentifier::Button(x)).SetPosition(vec3(temp.x, temp.y + 500, 50));
			
			if (x >= 2 && x <= 4 && isAnim[x - 2]) {
				m_register->get<Transform>(EntityIdentifier::Button(CameraChoice + 10 * x)).SetPosition(vec3(0, 500, 30));
			}
		}
		for (int x(1); x <= 4; x++) {
			m_register->get<Transform>(EntityIdentifier::Button(50 + x)).SetPosition(vec3(0, 500, 30));
		}
		m_register->get<Transform>(EntityIdentifier::Button(CameraChoice + 10)).SetPosition(vec3(0, 500, 25));
		m_register->get<Transform>(EntityIdentifier::Button(9)).SetPosition(vec3(50, 500, 40));
	}

	settingup = true;
}

void Set::Update()
{
	//check if static should be removed and adds/removees depending on hasStatic
	if (wait > 0) {
		if (hasStatic) {
			EffectManager::CreateEffect(Grain, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());
			GrainEffect* temp = (GrainEffect*)EffectManager::GetEffect(0);
			temp->SetStrength(500);
			EffectManager::CreateEffect(Pixelate, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());
			PixelateEffect* temp2 = (PixelateEffect*)EffectManager::GetEffect(1);
			temp2->SetPixelSize(10);
			hasStatic = false;
		}
		wait -= Timer::deltaTime;
		if (wait <= 0) {
			hasStatic = true;
		}
	}
	else {
		if (hasStatic) {
			EffectManager::RemoveEffect(0);
			EffectManager::RemoveEffect(0);
		}
		hasStatic = false;
	}
}

void Set::Reset(entt::registry* m_reg)
{
	//reset all variables
	m_register = m_reg;
	settingup = true;
	hasStatic = false;
	for (int x(0); x < 3; x++) {
		oldIsAnim[x] = false;
	}
	wait = 0;
}

MainMenu::MainMenu(std::string name)
	: Scene(name)
{
}

void MainMenu::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

#pragma region camera
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Camera>(entity);

		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Camera");
		ECS::SetIsMainCamera(entity, true);
	}
#pragma endregion

	//Button 0
#pragma region Loading Screen
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string filename = "loading.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(filename);

		animController.AddAnimation(Animation());

		animController.SetActiveAnim(0);

		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(0.f, 199.f), vec2(199.f, 0.f));
		anim.AddFrame(vec2(0.f, 399.f), vec2(199.f, 200.f));

		anim.SetRepeating(true);
		anim.SetSecPerFrame(0.5f);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 200, 200, true, &animController);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 200, 50.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "loading screen");
		ECS::SetIsButton(entity, true, 0);
	}
#pragma endregion

	srand(time(0));
	for (int x(1); x <= 5; x++) {

	//Button 1-8
#pragma region Night Buttons
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<AnimationController>(entity);

			std::string filename = "night buttons.png";
			auto& animController = ECS::GetComponent<AnimationController>(entity);
			animController.InitUVs(filename);

			animController.AddAnimation(Animation());
			animController.AddAnimation(Animation());

			animController.SetActiveAnim(0);

			auto& anim = animController.GetAnimation(0);
			anim.AddFrame(vec2(2.f, 14.f * x), vec2(66.f, 14.f * (x - 1) + 2.f));

			anim.SetRepeating(false);
			anim.SetSecPerFrame(0.1f);

			auto& anim2 = animController.GetAnimation(1);
			anim2.AddFrame(vec2(36.f - (rand() % 3 - 1) * (rand() % 36), 36.f - (rand() % 3 - 1) * (rand() % 36)), vec2(36.f - (rand() % 3 - 1) * (rand() % 36), 16.f * (x - 1) + 2.f));
			anim2.AddFrame(vec2(36.f - (rand() % 3 - 1) * (rand() % 36), 36.f - (rand() % 3 - 1) * (rand() % 36)), vec2(36.f - (rand() % 3 - 1) * (rand() % 36), 16.f * (x - 1) + 2.f));
			anim2.AddFrame(vec2(36.f - (rand() % 3 - 1) * (rand() % 36), 36.f - (rand() % 3 - 1) * (rand() % 36)), vec2(36.f - (rand() % 3 - 1) * (rand() % 36), 16.f * (x - 1) + 2.f));
			anim2.AddFrame(vec2(36.f - (rand() % 3 - 1) * (rand() % 36), 36.f - (rand() % 3 - 1) * (rand() % 36)), vec2(36.f - (rand() % 3 - 1) * (rand() % 36), 16.f * (x - 1) + 2.f));

			anim2.SetRepeating(true);
			anim2.SetSecPerFrame(0.1f);

			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 48, 9, true, &animController);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-65, 30 - x * 15, 25.f));
			
			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
			ECS::SetUpIdentifier(entity, bitHolder, "night button " + std::to_string(x));
			ECS::SetIsButton(entity, true, x);
		}
#pragma endregion

	}
}

void MainMenu::Update() { }
