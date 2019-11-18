#include "FNAFScene.h"

entt::registry* Set::m_register = nullptr;
bool Set::settingup = true;

FNAF::FNAF(std::string name)
	: Scene(name)
{
}

void FNAF::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

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

	/*
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string filename = "filename";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, sizex, sizey);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(x.f, y.f, z.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "name");
	*/
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

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string filename = "player.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 25, 15);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -50.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "player");
		ECS::SetIsMainPlayer(entity, true);
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -50.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "tracker");
		ECS::SetIsButton(entity, true, 0);
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string filename = "map.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 91.5, 81);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, 500.f, 40.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "map");
		ECS::SetIsButton(entity, true, 9);
	}

	for (int x(1); x <= 8; x++) {
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
			anim2.AddFrame(vec2(94.f, (22.f * x) - 1.f), vec2(137.f, 22.f * (x - 1) + 2.f));
			anim2.AddFrame(vec2(140.f, (22.f * x) - 1.f), vec2(183.f, 22.f * (x - 1) + 2.f));

			anim2.SetRepeating(false);
			anim2.SetSecPerFrame(0.1f);

			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 11, 5, true, &animController);

			switch (x) {
			case 1:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(23, 461.5f, 50.f));	break;
			case 2:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(54, 464.f, 50.f));	break;
			case 3:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(43, 485.5f, 50.f));	break;
			case 4:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(87.5, 460.5f, 50.f));	break;
			case 5:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(29, 445.f, 50.f));	break;
			case 6:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(74.5, 414.f, 50.f));	break;
			case 7:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(87.8, 423.4f, 50.f));	break;
			case 8:		ECS::GetComponent<Transform>(entity).SetPosition(vec3(29.5, 475.f, 50.f));	break;
			default: break;
			}

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
			ECS::SetUpIdentifier(entity, bitHolder, "button " + std::to_string(x));
			ECS::SetIsButton(entity, true, x);
		}
		
		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			std::string filename = "/rooms/" + std::to_string(x) + ".png";
			
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 200, 200);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 500.f, 25.f));

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "room " + std::to_string(x));
			ECS::SetIsButton(entity, true, x + 10);
		}

		/*{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			std::string filename = "/rooms/bonnie/" + std::to_string(x) + ".png";
			
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 200, 200);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 500.f, 25.f));

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "bonnie room " + std::to_string(x));
			ECS::SetIsButton(entity, true, x + 20);
		}

		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			std::string filename = "/rooms/freddy/" + std::to_string(x) + ".png";
			
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 200, 200);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 500.f, 25.f));

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "freddy room " + std::to_string(x));
			ECS::SetIsButton(entity, true, x + 30);
		}

		{
			auto entity = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			std::string filename = "/rooms/chica/" + std::to_string(x) + ".png";
			
			ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 200, 200);

			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 500.f, 25.f));

			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(entity, bitHolder, "chica room " + std::to_string(x));
			ECS::SetIsButton(entity, true, x + 40);
		}*/
	}


}

bool Set::positionTesting(int entity, vec3(otherposition))
{
	vec3(Pos) = otherposition - m_register->get<Transform>(entity).GetPosition();

	if (Pos.x <= m_register->get<Sprite>(entity).GetWidth() / 2.f &&
		Pos.x >= -m_register->get<Sprite>(entity).GetWidth() / 2.f &&
		Pos.y <= m_register->get<Sprite>(entity).GetHeight() / 2.f &&
		Pos.y >= -m_register->get<Sprite>(entity).GetHeight() / 2.f)
	{
		return true;
	}
	
	return false;
}

void Set::SetUpSet(int OldCameraChoice, int CameraChoice)
{
	//button reseting
	auto& temp = m_register->get<AnimationController>(EntityIdentifier::Button(OldCameraChoice));
	temp.SetActiveAnim(0);
	temp.GetAnimation(1).Reset();
	m_register->get<AnimationController>(EntityIdentifier::Button(CameraChoice)).SetActiveAnim(1);

	//Scene organisation here (CameraChoice is current, OldCameraChoice is previous), add 10 for rooms
	m_register->get<Transform>(EntityIdentifier::Button(OldCameraChoice + 10)).SetPosition(vec3(0, 500, 25));
	m_register->get<Transform>(EntityIdentifier::Button(CameraChoice + 10)).SetPosition(vec3(0, 0, 25));

	//map
	m_register->get<Transform>(EntityIdentifier::Button(9)).SetPosition(vec3(50, -50, 40.f));

	//camera buttons
	if (settingup) {
		for (int x(1); x <= 8; x++) {
			vec3 temp = m_register->get<Transform>(EntityIdentifier::Button(x)).GetPosition();
			m_register->get<Transform>(EntityIdentifier::Button(x)).SetPosition(vec3(temp.x, temp.y - 500, 50));
		}
		settingup = false;
	}
}

void Set::UndoSet(int CameraChoice)
{
	for (int x(1); x <= 8; x++) {
		vec3 temp = m_register->get<Transform>(EntityIdentifier::Button(x)).GetPosition();
		m_register->get<Transform>(EntityIdentifier::Button(x)).SetPosition(vec3(temp.x, temp.y + 500, 50));
	}
	m_register->get<Transform>(EntityIdentifier::Button(CameraChoice + 10)).SetPosition(vec3(0, 500, 25));
	m_register->get<Transform>(EntityIdentifier::Button(9)).SetPosition(vec3(50, 500, 40));
	settingup = true;
}

void Set::GetRegister(entt::registry* m_reg)
{
	m_register = m_reg;
}
