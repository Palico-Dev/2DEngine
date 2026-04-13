#include "GameCore.h"
#include "PlayerController.h"
#include "InputManager.h"
#include "Entity.h"
#include "Transform.h"
#include "EngineTime.h"
#include "AssetManager.h"
#include "Random.h"
#include "Collider.h"
#include "GameController.h"
#include "SaveManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "NetworkEngine.h"
#include "NetworkComponent.h"
#include "Bullet.h"

IMPLEMENT_DYNAMIC_CLASS(PlayerController)

void PlayerController::Initialize()
{
	Component::Initialize();

	InputManager::Instance().BindAction("walk_up", SDLK_w);
	InputManager::Instance().BindAction("walk_up", SDLK_UP);

	InputManager::Instance().BindAction("walk_down", SDLK_s);
	InputManager::Instance().BindAction("walk_down", SDLK_DOWN);

	InputManager::Instance().BindAction("walk_left", SDLK_a);
	InputManager::Instance().BindAction("walk_left", SDLK_LEFT);

	InputManager::Instance().BindAction("walk_right", SDLK_d);
	InputManager::Instance().BindAction("walk_right", SDLK_RIGHT);

	if (Engine::Instance().GetRole() == EngineRole::Client)
	{
		allocateAuthorityCallback = std::bind(&PlayerController::OnAllocateAuthority, this,
			std::placeholders::_1, std::placeholders::_2);
		NetworkEngine::Instance().RegisterPacketCallback(ID_ALLOCATE_AUTHORITY, &allocateAuthorityCallback);
	}

	owner->GetComponent<NetworkComponent>()->RegisterRPC("RPC_Move", [this](RakNet::BitStream& bs)
		{
			this->RPC_Move(bs);
		});

	owner->GetComponent<NetworkComponent>()->RegisterRPC("RPC_Shoot", [this](RakNet::BitStream& bs)
		{
			this->RPC_Shoot(bs);
		});
}

Component* PlayerController::Clone()
{
	PlayerController* clone = (PlayerController*)CreateObject("PlayerController");

	*clone = *this;

	clone->owner = nullptr;
	return clone;
}

void PlayerController::OnTriggerEnter(Collider* other)
{

}

void PlayerController::MovementBounds(glm::vec2& dir)
{

	glm::vec2 pos = owner->transform->GetPosition();

	int x = dir.x;
	int y = dir.y;

	if (pos.x < 20)
		x = std::max(x, 0);
	if (pos.x > 730)
		x = std::min(x, 0);
	if (pos.y < 20)
		y = std::max(y, 0);
	if (pos.y > 980)
		y = std::min(y, 0);

	dir = { x,y };
}

void PlayerController::OnAllocateAuthority(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)
{
	unsigned int networkId = 0;
	networkId = PeakBitStream<unsigned int>(_bStream);

	if (owner->GetComponent<NetworkComponent>()->networkId == networkId)
	{
		Debug::Log("[PlayerController] Authority allocated for networkId: " + std::to_string(networkId));
		hasAuthority = true;
	}
	else{
		Debug::Log("[PlayerController] Authority NOT allocated for networkId: " + std::to_string(networkId));
	}
}

void PlayerController::RPC_Move(RakNet::BitStream& _bStream)
{
	float value = 0.0f;
	_bStream.Read(value);
	movement.x += value;
	_bStream.Read(value);
	movement.y += value;
}

void PlayerController::RPC_Shoot(RakNet::BitStream& _bStream)
{
	glm::vec2 playerPos;
	glm::vec2 dir;
	_bStream.Read(playerPos.x);
	_bStream.Read(playerPos.y);
	_bStream.Read(dir.x);
	_bStream.Read(dir.y);

	Entity* bullet = Gameplay::Spawn(bulletAsset, playerPos);
	bullet->GetComponent<Bullet>()->SetDirection(dir);
}

void PlayerController::GetDamage()
{
	health--;
	if (health <= 0)
	{
		health = maxHealth;
	}
}

void PlayerController::Update()
{
	Component::Update();
	if (!GameController::Instance().isGameStarted)
		return;

	if (Engine::Instance().GetRole() == EngineRole::Client)
	{
		if (!hasAuthority)
			return;

		movement = glm::vec2(0, 0);

		if (InputManager::Instance().GetKeyPressed(SDLK_SPACE))
		{
			Debug::Log("Space");
		}
		if (InputManager::Instance().GetMousePressed(SDL_BUTTON_LEFT))
		{
			glm::vec2 mousePos = CollisionMath::PointToVector2(InputManager::Instance().GetMousePosition());
			glm::vec2 playerPos = owner->transform->GetPosition();
			glm::vec2 dir = mousePos - playerPos;
			dir = normalize(dir);

			RakNet::BitStream bs;
			bs.Write(playerPos.x);
			bs.Write(playerPos.y);
			bs.Write(dir.x);
			bs.Write(dir.y);
			Gameplay::SendRPC(owner, "RPC_Shoot", bs);
		}

		movement.x = InputManager::Instance().GetAxis("walk_left", "walk_right");
		movement.y = InputManager::Instance().GetAxis("walk_up", "walk_down");

		MovementBounds(movement);


		if (glm::length(movement) != 0.0f)
		{
			movement = glm::normalize(movement);
			movement = movement * speed * Time::Instance().DeltaTime();

			RakNet::BitStream bs;
			bs.Write(movement.x);
			bs.Write(movement.y);
			Gameplay::SendRPC(owner, "RPC_Move", bs);
		}
	}

	if (glm::length(movement) != 0.0f)
	{
		owner->transform->Translate(movement);
		movement = glm::vec2(0, 0);
	}

}

void PlayerController::Start()
{
	bulletAsset = AssetManager::Instance().GetAsset<PrefabAsset>("bullet.prefab");
}
