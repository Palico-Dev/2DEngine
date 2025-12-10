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

void PlayerController::GetDamage()
{
	health--;
	if (health <= 0)
	{
		GameController::Instance().LoseHealth();
		health = maxHealth;
	}
}

void PlayerController::Update()
{
	Component::Update();
	glm::vec2 direction = { 0, 0 };

	if (InputManager::Instance().GetKeyPressed(SDLK_SPACE))
	{
		Entity* e = Gameplay::Spawn(bulletAsset, owner->transform->GetPosition()+glm::vec2(0,-20));
	}
	if (InputManager::Instance().GetKeyPressed(SDLK_BACKQUOTE))
	{
		SaveManager::Instance().SaveGame();
	}
	if (InputManager::Instance().GetKeyPressed(SDLK_l))
	{
		SceneManager::Instance().GetCurrentScene()->CleanScene();
		SaveManager::Instance().LoadGame();
	}

	
	direction.x = InputManager::Instance().GetAxis("walk_left", "walk_right");
	direction.y = InputManager::Instance().GetAxis("walk_up", "walk_down");
	//Debug::Log(glm::to_string(direction));
	owner->transform->Translate(direction * speed * Time::Instance().DeltaTime());
}

void PlayerController::Start()
{
	Debug::Log("PlayerController Start");
	bulletAsset = AssetManager::Instance().GetAsset<PrefabAsset>("bullet.prefab");


}
