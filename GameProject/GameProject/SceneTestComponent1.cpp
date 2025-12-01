#include "GameCore.h"
#include "SceneTestComponent1.h"
#include "Entity.h"
#include "Scene.h"
#include "SceneManager.h"
#include "InputManager.h"

IMPLEMENT_DYNAMIC_CLASS(SceneTestComponent1)
IMPLEMENT_DYNAMIC_CLASS(ZombieAIComponent)
IMPLEMENT_DYNAMIC_CLASS(ZombiePlayingComponent)
IMPLEMENT_DYNAMIC_CLASS(ZombieFactoryComponent)
IMPLEMENT_DYNAMIC_CLASS(AngelAIComponent)
IMPLEMENT_DYNAMIC_CLASS(AngelPlayingComponent)
IMPLEMENT_DYNAMIC_CLASS(AngelFactoryComponent)

extern void Game_Register();
void SceneTestComponent1::Initialize()
{
}

void SceneTestComponent1::Update()
{
}

void ZombieAIComponent::OnComponentInitialized()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	DEBUG_LOG(3, "[Zombie #" + std::to_string(GetOwner()->GetId()) + "] Initialized and ready to search for food.");
}

void ZombieAIComponent::Update()
{
	Component::Update();
	timer += Time::Instance().DeltaTime();

	if (timer < timeToSearch)
	{
		return;
	}

	timer = 0.0f;

	unsigned int id = GetOwner()->GetId();
	DEBUG_LOG(3, "[Zombie #" + std::to_string(id) + "] is looking for food...");

	int r = std::rand() % 100;
	if(r < 40)
	{
		StarvingTime++;
		DEBUG_LOG(3, "[Zombie #" + std::to_string(id) + "] Food not found, Zombie is starving! Starving time: "
			+ std::to_string(StarvingTime) + " seconds.");
	}
	else {
		DEBUG_LOG(3, "[Zombie #" + std::to_string(id) + "] Food found, Zombie is not starving. Lucky day.");
	}

	if(StarvingTime >= 2)
	{
		DEBUG_LOG(3, "[Zombie #" + std::to_string(id) + "] Zombie has starved to death!");
		GetOwner()->MarkForDestroy();
	}
}


void ZombiePlayingComponent::OnComponentInitialized()
{
	DEBUG_LOG(3, "[Zombie #" + std::to_string(GetOwner()->GetId()) + "] Initialized and ready to play.");
}

void ZombiePlayingComponent::Update()
{
	Component::Update();
	timer += Time::Instance().DeltaTime();

	if (timer < timeToSearch)
	{
		return;
	}

	timer = 0.0f;
	unsigned int id = GetOwner()->GetId();
	DEBUG_LOG(3, "[Zombie #" + std::to_string(id) + "] is playing around happily...");
}

void ZombieFactoryComponent::OnComponentInitialized()
{
	DEBUG_LOG(2, "[ZombieFactory] Initialized and ready to spawn Zombies.");
}

void ZombieFactoryComponent::Update()
{
	Component::Update();
	SceneManager& sm = SceneManager::Instance();
	Scene* testScene = sm.GetActiveScene();

	if (InputManager::Instance().GetKeyPressed(SDLK_s)) {
		DEBUG_LOG(1, "Switching to Level2 scene...");
		sm.QueueActiveScene("Level2");
	}
	if (InputManager::Instance().GetKeyPressed(SDLK_SPACE)) {
		Component* comp = GetOwner()->FindFirstComponentByType("Transform");
		if (comp)
			DEBUG_LOG(2, comp->GetDerivedTypeClassName());
	}
	timer += Time::Instance().DeltaTime() ;
	if (timer < spawn_delay)
	{
		return;
	}
	timer = 0.0f;
	
	
	Entity* entity = testScene->CreateEntity({ "ZombiePlayingComponent", "ZombieAIComponent" });

	DEBUG_LOG(2, "[ZombieFactory] Spawned a new Zombie with ID #" + std::to_string(entity->GetId()));
}

void MTB_251123()
{
	try
	{
		Game_Register();

		std::ifstream test("../Assets/Scenes/CollisionTest.json");
		if (!test.is_open())
			std::cout << "Failed to open CollisionTest.json\n";

		Engine::Instance().Initialize();

		SceneManager& sm = SceneManager::Instance();

		/*Scene* testScene = sm.GetActiveScene();
		testScene->CreateEntity({ "ZombieFactoryComponent" });*/

		sm.RegisterScene("CollisionTest", "../Assets/Scenes/CollisionTest.json");
		sm.SetStartupScene("CollisionTest");

		Engine::Instance().GameLoop();
		Engine::Instance().Destroy();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
}

void AngelFactoryComponent::OnComponentInitialized()
{
	DEBUG_LOG(2, "[AngelFactory] Initialized and ready to spawn Angels.");
}

void AngelFactoryComponent::Update()
{
	Component::Update();
	SceneManager& sm = SceneManager::Instance();
	Scene* testScene = sm.GetActiveScene();

	if (InputManager::Instance().GetKeyPressed(SDLK_s)) {
		DEBUG_LOG(1, "Switching to Level1 scene...");
		sm.QueueActiveScene("Level1");
	}
	if (InputManager::Instance().GetKeyPressed(SDLK_SPACE)) {
		Component* comp = GetOwner()->FindFirstComponentByType("Transform");
		if(comp)
			DEBUG_LOG(2, comp->GetDerivedTypeClassName());
	}
	timer += Time::Instance().DeltaTime();
	if (timer < spawn_delay)
	{
		return;
	}
	timer = 0.0f;


	Entity* entity = testScene->CreateEntity({ "AngelPlayingComponent", "AngelAIComponent" });

	DEBUG_LOG(4, "AngelFactory] Spawned a new Angel with ID #" + std::to_string(entity->GetId()));

}
void MTB_251125() {
	try
	{
		Game_Register();

		Engine::Instance().Initialize();
		Engine::Instance().GameLoop();
		Engine::Instance().Destroy();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
}

void AngelPlayingComponent::Update()
{
	Component::Update();
	timer += Time::Instance().DeltaTime();

	if (timer < 3)
	{
		return;
	}

	timer = 0.0f;
	unsigned int id = GetOwner()->GetId();
	DEBUG_LOG(4, "[Angel #" + std::to_string(id) + "] is playing around happily...");
}

void AngelPlayingComponent::OnComponentInitialized()
{
	DEBUG_LOG(4, "[Angel #" + std::to_string(GetOwner()->GetId()) + "] Initialized and ready to play.");
}

void AngelAIComponent::OnComponentInitialized()
{
	DEBUG_LOG(4, "[Angel #" + std::to_string(GetOwner()->GetId()) + "] Initialized and ready to search for humans.");
}

void AngelAIComponent::Update()
{
	timer += Time::Instance().DeltaTime();

	if (timer < timeToSearch)
	{
		return;
	}

	timer = 0.0f;
	 
	unsigned int id = GetOwner()->GetId();
	DEBUG_LOG(4, "[Angel #" + std::to_string(id) + "] is looking for humans...");

	int r = std::rand() % 100;
	if (r < 40)
	{
		MissHumansTime++;
		DEBUG_LOG(4, "[Angel #" + std::to_string(id) + "] Humans not found, Angel is sad! Sad time: "
			+ std::to_string(MissHumansTime) + " seconds.");
	}
	else {
		DEBUG_LOG(4, "[Angel #" + std::to_string(id) + "] Humans found, Angel is happy! Lucky day.");
	}

	if (MissHumansTime >= 2)
	{
		DEBUG_LOG(4, "[Angel #" + std::to_string(id) + "] Angel couldn't find humans and is ascending back to heaven.");
		GetOwner()->MarkForDestroy();
	}
}
