#include "EngineCore.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "RenderSystem.h"
#include "AssetManager.h"
#include "TextureAsset.h"

IMPLEMENT_ABSTRACT_CLASS(Collider);


void Collider::Initialize()
{
	if (initialized)
		return;
	Component::Initialize();

	CollisionSystem::Instance().AddCollider(this);

#if COLLISIONTEST
	return;
#endif

	lastPosition = owner->transform->GetPosition();
	lastRotation = owner->transform->GetRotation();
	lastScale = owner->transform->GetScale();

	if (isRendered)
	{
		SDL_Renderer* r = RenderSystem::Instance().GetRenderer();
		TextureAsset* t;
		switch (GetType())
		{
		case ColliderType::Box:
			t = AssetManager::Instance().GetEngineAsset<TextureAsset>("ColliderBox");
			debugTexture = t->GetTexture();
			if (!debugTexture)
				Debug::Warning("Fail to load ColliderBox Texture!");
			break;

		case ColliderType::Circle:
			t = AssetManager::Instance().GetEngineAsset<TextureAsset>("ColliderCircle");
			debugTexture = t->GetTexture();
			if (!debugTexture)
				Debug::Warning("Fail to load ColliderBox Texture!");
			break;
		}
		SDL_SetTextureColorMod(debugTexture, 0, 255, 0);
		SDL_SetTextureAlphaMod(debugTexture, 50);
		layer = 10;
		OnEnable();
	}
}

void Collider::Destroy()
{
	Component::Destroy();
	CollisionSystem::Instance().RemoveCollider(this);
}

glm::vec2 Collider::GetCenterWorld() const
{
#if COLLISIONTEST
	return center;
#endif
	Transform* t = owner->transform;
	glm::vec2 s = t->GetScale();
	float r = t->GetRotation();

	glm::vec2 c = GetCenter();

	glm::vec2 scaled = { (c.x * s.x), (c.y * s.y) };

	glm::vec2 rotated = {
		scaled.x * cos(r) - scaled.y * sin(r),
		scaled.x * sin(r) + scaled.y * cos(r)
	};

	return t->GetPosition() + rotated;
}


void Collider::Render()
{
#ifdef _DEBUG

	//skip if invisible or has missing texture
	if (!isRendered || !debugTexture) return;

	Transform* t = owner->transform;
	SDL_FRect destinationRect;

	switch (GetType())
	{
	case ColliderType::Box:
	{
		BoxCollider* box = static_cast<BoxCollider*>(this);
		destinationRect.w = box->GetSize().x * t->GetScale().x;
		destinationRect.h = box->GetSize().y * t->GetScale().y;
		break;
	}
	case ColliderType::Circle:
	{
		CircleCollider* circle = static_cast<CircleCollider*>(this);
		float r = circle->GetRadiusWorld();
		destinationRect.w = r * 2.0f;
		destinationRect.h = r * 2.0f;
		break;
	}
	default:
		destinationRect.w = 256 * t->GetScale().x;
		destinationRect.h = 256 * t->GetScale().y;
		break;
	}

	destinationRect.x = t->GetPosition().x - destinationRect.w * 0.5f;
	destinationRect.y = t->GetPosition().y - destinationRect.h * 0.5f;

	SDL_FPoint rotationCenter = { destinationRect.w * 0.5f, destinationRect.h * 0.5f };

	SDL_RenderCopyExF(
		RenderSystem::Instance().GetRenderer(), //renderer
		debugTexture,                           //texture
		nullptr,                                //full
		&destinationRect,                       //size
		t->GetRotationDegrees(),                //rotation angle
		&rotationCenter,                        //rotation around rect center
		SDL_FLIP_NONE                           //mirroring?
	);

#endif
}

void Collider::Load(json::JSON& _jsonData)
{
	Component::Load(_jsonData);

	center = FileManager::JsonReadVec2(_jsonData, "center");
	isTrigger = FileManager::JsonReadBool(_jsonData, "isTrigger");
	isStatic = FileManager::JsonReadBool(_jsonData, "isStatic");
	isRendered = FileManager::JsonReadBool(_jsonData, "isRendered");
	layer = FileManager::JsonReadInt(_jsonData, "layer");
}

void Collider::Serialize(json::JSON& j)
{
	FileManager::JsonWriteVec2(j, "center", center);
	FileManager::JsonWriteBool(j, "isTrigger", isTrigger);
	FileManager::JsonWriteBool(j, "isStatic", isStatic);
	FileManager::JsonWriteBool(j, "isRendered", isRendered);
	FileManager::JsonWriteInt(j, "layer", layer);

}

void Collider::Deserialize(json::JSON& j)
{
	center = FileManager::JsonReadVec2(j, "center");
	isTrigger = FileManager::JsonReadBool(j, "isTrigger");
	isStatic = FileManager::JsonReadBool(j, "isStatic");
	isRendered = FileManager::JsonReadBool(j, "isRendered");
	layer = FileManager::JsonReadInt(j, "layer");
}
