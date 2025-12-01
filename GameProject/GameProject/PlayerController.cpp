#include "GameCore.h"
#include "PlayerController.h"
#include "InputManager.h"
#include "Entity.h"
#include "Transform.h"
#include "EngineTime.h"

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

void PlayerController::Update()
{
	Component::Update();
	glm::vec2 direction = { 0, 0 };
	
	direction.x = InputManager::Instance().GetAxis("walk_left", "walk_right");
	direction.y = InputManager::Instance().GetAxis("walk_up", "walk_down");
	
	GetOwner()->GetTransform()->SetPosition(GetOwner()->GetTransform()->GetPosition()+direction*speed* Time::Instance().DeltaTime());
}
