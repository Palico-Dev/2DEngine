#include "EngineCore.h"
#include "NetworkComponent.h"
#include "NetworkEngine.h"
#include "FileManager.h"

IMPLEMENT_DYNAMIC_CLASS(NetworkComponent);
CLONEABLE_IMPLEMENT(NetworkComponent)

void NetworkComponent::Load(json::JSON& data)
{
	prefabName = FileManager::JsonReadString(data, "prefabName");
	Debug::Log("[Network] Loaded network component from: " + prefabName);
}

