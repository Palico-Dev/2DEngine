#include "GameCore.h"
#include "Engine.h"
#include "ZombieFactory.h"
#include "Sprite.h"

IMPLEMENT_DYNAMIC_CLASS(ZombieFactory)

void ZombieFactory::Initialize()
{
    Component::Initialize();

    spawn_delay = 1.0f;
}

void ZombieFactory::Update()
{
    Component::Update();

    current_spawn_delay += Time::Instance().DeltaTime();
    if (current_spawn_delay > spawn_delay)
    {
        current_spawn_delay = 0.0f;
        std::vector<std::string> comp_list = { "Zombie", "Sprite" };
        Entity* entity = Scene::Instance().CreateEntity(comp_list);

        Sprite* const sprite = static_cast<Sprite*>(entity->FindComponentByType("Sprite"));
        sprite->SetTexture("../Assets/Textures/zombie-head-icon.png");
    }
}