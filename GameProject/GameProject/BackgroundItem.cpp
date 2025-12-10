#include "GameCore.h"
#include "BackgroundItem.h"
#include "Entity.h"
#include "Transform.h"
#include "TextureAsset.h"
#include "Sprite.h"
#include "FileManager.h"

IMPLEMENT_DYNAMIC_CLASS(BackgroundItem)
CLONEABLE_IMPLEMENT(BackgroundItem)

void BackgroundItem::Init(TextureAsset* texture, glm::vec2 size, float newSpeed)
{
	owner->GetComponent<Sprite>()->SetTexture(texture);
	owner->GetComponent<Sprite>()->SetSize(size);
	speed = newSpeed;
}

void BackgroundItem::Serialize(json::JSON& j)
{
	FileManager::JsonWriteFloat(j, "speed", speed);
}

void BackgroundItem::Deserialize(json::JSON& j)
{
	speed = FileManager::JsonReadFloat(j, "speed");
}

void BackgroundItem::Update()
{
	if (speed == 0.0f)
		return;
	owner->transform->Translate(glm::vec2(0, 1) * speed * Time::Instance().DeltaTime());

	if (owner->transform->GetPosition().y > 1200.0f)
		Gameplay::Destroy(owner);
}
