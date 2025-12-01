#include "EngineCore.h"
#include "PrefabAsset.h"
#include "Entity.h"

IMPLEMENT_DYNAMIC_CLASS(PrefabAsset)

void PrefabAsset::Load()
{
    json::JSON entityItem = LoadJson(path);
    m_Entity = static_cast<Entity*>(CreateObject("Entity"));

    if (m_Entity == nullptr)
    {
        std::cout << "Error: Failed Prefab: " << path << std::endl;
        return;
    }
    m_Entity->Load(entityItem);

    if (m_Entity->GetTransform() == nullptr)
    {
        // Ensure every Entity has a Transform
        m_Entity->CreateComponent("Transform");
    }
}

void PrefabAsset::Destroy()
{
    m_Entity = nullptr;
}
