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
			t = (TextureAsset*)AssetManager::Instance().GetEngineAsset("ColliderBox");
			debugTexture = t->GetTexture();
			if (!debugTexture)
				Debug::Warning("Fail to load ColliderBox Texture!");
			break;

		case ColliderType::Circle:
			t = (TextureAsset*)AssetManager::Instance().GetEngineAsset("ColliderCircle");
			debugTexture = t->GetTexture();
			if (!debugTexture)
				Debug::Warning("Fail to load ColliderBox Texture!");
			break;
		}
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
}

void Collider::Load(json::JSON& _jsonData)
{
	Component::Load(_jsonData);

	if (_jsonData.hasKey("center"))
	{
		auto c = _jsonData["center"];
		center.x = c["x"].ToFloat();
		center.y = c["y"].ToFloat();
	}
	if (_jsonData.hasKey("isTrigger")) isTrigger = _jsonData["isTrigger"].ToBool();
	if (_jsonData.hasKey("layer")) layer = _jsonData["layer"].ToInt();
	if (_jsonData.hasKey("isStatic")) isStatic = _jsonData["isStatic"].ToBool();
	if (_jsonData.hasKey("isRendered"))
		isRendered = _jsonData["isRendered"].ToBool();
}