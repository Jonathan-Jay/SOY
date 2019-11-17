#include "FNAFScene.h"

entt::registry* Set::m_register = nullptr;

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

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(00.f, 0.f, -50.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "room");
		ECS::SetIsButton(entity, true, 2);
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
		ECS::SetIsButton(entity, true, 1);
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -50.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "tracker");
		ECS::SetIsButton(entity, true, 0);
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

void Set::SetUpSet(int CamerChoice)
{
}

void Set::UndoSet()
{
}

void Set::GetRegister(entt::registry* m_reg)
{
	m_register = m_reg;
}
