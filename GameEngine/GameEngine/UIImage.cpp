#include "EngineCore.h"
#include "UIImage.h"
#include "FileManager.h"
#include "AssetManager.h"
#include "TextureAsset.h"
#include "RenderSystem.h"

IMPLEMENT_DYNAMIC_CLASS(UIImage)

void UIImage::Initialize()
{
	if (initialized)
		return;
	Widget::Initialize();
}

void UIImage::Destroy()
{
	Widget::Destroy();
}

void UIImage::Update()
{
	Widget::Update();
}

void UIImage::Load(json::JSON j)
{
	Widget::Load(j);

	size = FileManager::JsonReadVec2(j, "size");
	color = FileManager::JsonReadColor(j, "color");

	std::string flipString = FileManager::JsonReadString(j, "flip");
	if (flipString == "SDL_FLIP_NONE")
		flip = SDL_FLIP_NONE;
	else if (flipString == "SDL_FLIP_VERTICAL")
		flip = SDL_FLIP_VERTICAL;
	else if (flipString == "SDL_FLIP_HORIZONTAL")
		flip = SDL_FLIP_HORIZONTAL;

	if (!j.hasKey("asset"))
	{
		Debug::Warning("Texture are missing!!!");
		textureAsset = (TextureAsset*)AssetManager::Instance().GetEngineAsset("DefaultTexture");
	}
	else
	{
		textureAsset = (TextureAsset*)AssetManager::Instance().GetAsset(FileManager::JsonReadString(j, "asset").c_str());
	}
}

void UIImage::OnRender()
{

	float renderW = size.x;
	float renderH = size.y;

	glm::vec2 parentPos = parent->GetPosition();
	float ownerAngleDeg = parent->GetRotation();

	float angleRad = ownerAngleDeg * (M_PI / 180.0f);

	float rotatedOffsetX = (localPosition.x * std::cos(angleRad)) - (localPosition.y * std::sin(angleRad));
	float rotatedOffsetY = (localPosition.x * std::sin(angleRad)) + (localPosition.y * std::cos(angleRad));

	float finalCenterX = parentPos.x + rotatedOffsetX;
	float finalCenterY = parentPos.y + rotatedOffsetY;

	SDL_FRect renderQuad = {
		finalCenterX - (renderW * 0.5f),
		finalCenterY - (renderH * 0.5f),
		renderW,
		renderH
	};

	float finalRenderAngle = ownerAngleDeg + rotation;

	SDL_Texture* tex = textureAsset->GetTexture();

	Uint8 r = static_cast<Uint8>(color.r * 255.0f);
	Uint8 g = static_cast<Uint8>(color.g * 255.0f);
	Uint8 b = static_cast<Uint8>(color.b * 255.0f);
	Uint8 a = static_cast<Uint8>(color.a * 255.0f);

	SDL_SetTextureColorMod(tex, r, g, b);
	SDL_SetTextureAlphaMod(tex, a);

	SDL_RenderCopyExF(
		RenderSystem::Instance().GetRenderer(),
		tex,
		NULL,               // clip
		&renderQuad,        // The calculated world position
		finalRenderAngle,   // Total Angle
		NULL,               // NULL center = Rotate around Sprite's OWN center
		flip
	);

	SDL_SetTextureColorMod(tex, 255, 255, 255);
	SDL_SetTextureAlphaMod(tex, 255);
}
