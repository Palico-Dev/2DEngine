#include "EngineCore.h"
#include "Sprite.h"
#include "Entity.h"
#include "RenderSystem.h"
#include "Transform.h"
#include "AssetManager.h"
#include "FileManager.h"

IMPLEMENT_DYNAMIC_CLASS(Sprite);

void Sprite::Initialize()
{
	Component::Initialize();
}

void Sprite::Destroy()
{
	Component::Destroy();
	textureAsset = nullptr;
}

void Sprite::Update()
{
	Component::Update();
}

void Sprite::Load(json::JSON& _document)
{
	Component::Load(_document);
	spriteName = FileManager::JsonReadString(_document, "name");
	layer = FileManager::JsonReadInt(_document, "layer");

	if (!_document.hasKey("asset"))
	{
		Debug::Warning("Texture are missing!!!");
		textureAsset = (TextureAsset*)AssetManager::Instance().GetEngineAsset("DefaultTexture");
	}
	else
	{
		textureAsset = (TextureAsset*)AssetManager::Instance().GetAsset(FileManager::JsonReadString(_document, "asset").c_str());
	}

	size = FileManager::JsonReadVec2(_document, "size");
	offset = FileManager::JsonReadVec2(_document, "offset");

	std::string flipString = FileManager::JsonReadString(_document, "flip");
	if (flipString == "SDL_FLIP_NONE")
		flip = SDL_FLIP_NONE;
	else if (flipString == "SDL_FLIP_VERTICAL")
		flip = SDL_FLIP_VERTICAL;
	else if (flipString == "SDL_FLIP_HORIZONTAL")
		flip = SDL_FLIP_HORIZONTAL;

	rotation = FileManager::JsonReadFloat(_document, "rotation");
}

void Sprite::Render()
{
	float renderW = size.x;
	float renderH = size.y;

	glm::vec2 ownerPos = owner->transform->GetPosition();
	float ownerAngleDeg = owner->transform->GetRotationDegrees();

	float angleRad = ownerAngleDeg * (M_PI / 180.0f);

	float rotatedOffsetX = (offset.x * std::cos(angleRad)) - (offset.y * std::sin(angleRad));
	float rotatedOffsetY = (offset.x * std::sin(angleRad)) + (offset.y * std::cos(angleRad));

	float finalCenterX = ownerPos.x + rotatedOffsetX;
	float finalCenterY = ownerPos.y + rotatedOffsetY;

	SDL_FRect renderQuad = {
		finalCenterX - (renderW * 0.5f),
		finalCenterY - (renderH * 0.5f),
		renderW,
		renderH
	};

	float finalRenderAngle = ownerAngleDeg + rotation;

	SDL_RenderCopyExF(
		RenderSystem::Instance().GetRenderer(),
		textureAsset->GetTexture(),
		NULL,               // clip
		&renderQuad,        // The calculated world position
		finalRenderAngle,   // Total Angle
		NULL,               // NULL center = Rotate around Sprite's OWN center
		flip
	);
}