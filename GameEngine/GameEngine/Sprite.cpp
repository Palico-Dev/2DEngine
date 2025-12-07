#include "EngineCore.h"
#include "Sprite.h"
#include "Entity.h"
#include "RenderSystem.h"
#include "Transform.h"
#include "AssetManager.h"
#include "FileManager.h"

IMPLEMENT_DYNAMIC_CLASS(Sprite);

void Sprite::SetColor(glm::vec4 c)
{
	float r = std::clamp(c.r, 0.0f, 1.0f);
	float g = std::clamp(c.g, 0.0f, 1.0f);
	float b = std::clamp(c.b, 0.0f, 1.0f);
	float a = std::clamp(c.a, 0.0f, 1.0f);

	color = { r,g,b,a };
}

void Sprite::Initialize()
{
	if (initialized)
		return;
	Component::Initialize();

	OnEnable();
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

	color = FileManager::JsonReadColor(_document, "color");


}

Component* Sprite::Clone()
{
	Sprite* clone = (Sprite*)CreateObject("Sprite");

	*clone = *this;

	clone->owner = nullptr;
	return clone;
}

void Sprite::Render()
{
	// 1. Get the Scale
	glm::vec2 scale = owner->transform->GetScale();

	// 2. Calculate the Final Size on Screen
	// Since clip is NULL, we just stretch the 'size' by the scale.
	// Ensure 'size' was initialized to the Texture's width/height in your Load() function!
	float renderW = size.x * scale.x;
	float renderH = size.y * scale.y;

	// 3. SCALE THE OFFSET (Crucial Step!)
	// If we scale the image, we must also scale the distance from the pivot.
	float scaledOffsetX = offset.x * scale.x;
	float scaledOffsetY = offset.y * scale.y;

	// 4. Calculate Rotation Pivot
	glm::vec2 ownerPos = owner->transform->GetPosition();
	float ownerAngleDeg = owner->transform->GetRotationDegrees();
	float angleRad = ownerAngleDeg * (M_PI / 180.0f);

	// Use the SCALED offset for rotation math
	float rotatedOffsetX = (scaledOffsetX * std::cos(angleRad)) - (scaledOffsetY * std::sin(angleRad));
	float rotatedOffsetY = (scaledOffsetX * std::sin(angleRad)) + (scaledOffsetY * std::cos(angleRad));

	float finalCenterX = ownerPos.x + rotatedOffsetX;
	float finalCenterY = ownerPos.y + rotatedOffsetY;
	// ---- THE FIX: SNAP TO PIXEL ----
	// We calculate the float position, but we ROUND it to the nearest whole number.
	// This prevents drawing at "97.5px", forcing it to "98.0px".
	float destX = std::round(finalCenterX - (renderW * 0.5f));
	float destY = std::round(finalCenterY - (renderH * 0.5f));

	// 5. Build the Destination Quad
	// This centers the Quad around the calculated point
	SDL_FRect renderQuad = {
			destX,
			destY,
			renderW, // Keep size as float (for scaling)
			renderH
	};

	// 6. Render
	SDL_Texture* tex = textureAsset->GetTexture();

	// Set Colors
	Uint8 r = static_cast<Uint8>(color.r * 255.0f);
	Uint8 g = static_cast<Uint8>(color.g * 255.0f);
	Uint8 b = static_cast<Uint8>(color.b * 255.0f);
	Uint8 a = static_cast<Uint8>(color.a * 255.0f);
	SDL_SetTextureColorMod(tex, r, g, b);
	SDL_SetTextureAlphaMod(tex, a);

	// Draw
	SDL_RenderCopyExF(
		RenderSystem::Instance().GetRenderer(),
		tex,
		NULL,               // ALWAYS NULL (Draws the whole image)
		&renderQuad,        // The Scaled Destination
		ownerAngleDeg + rotation,
		NULL,               // Center (NULL = Rotate around center of renderQuad)
		flip
	);

	// Reset Colors
	SDL_SetTextureColorMod(tex, 255, 255, 255);
	SDL_SetTextureAlphaMod(tex, 255);
}