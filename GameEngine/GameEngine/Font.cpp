#include "EngineCore.h"
#include "Font.h"
#include "Entity.h"
#include "Transform.h"
#include "Component.h"
#include "RenderSystem.h"
#include "AssetManager.h"
#include "FontAsset.h"

IMPLEMENT_DYNAMIC_CLASS(Font);

void Font::Initialize()
{
	Component::Initialize();
}

void Font::Destroy()
{
	Component::Destroy();
	RenderSystem::Instance().RemoveRenderable(this);
	// Cleanup of FontAsset will be handled by AssetManager
	font = nullptr;
	if (message != nullptr) delete message;
}

void Font::Update()
{
	Component::Update();
}

void Font::Load(json::JSON& _document)
{
	Component::Load(_document);
	if (_document.hasKey("name")) fontName = _document["fontName"].ToString();

	//if (_document.hasKey("asset")) font = AssetManager::Instance().GetAsset<FontAsset>(_document["asset"].ToString().c_str());
	size = font->GetFontSize();

	if (_document.hasKey("text")) text = _document["text"].ToString();

	if (_document.hasKey("color"))
	{
		json::JSON colorData = _document["color"];
		if (colorData.hasKey("r")) color.r = colorData["r"].ToFloat();
		if (colorData.hasKey("g")) color.g = colorData["g"].ToFloat();
		if (colorData.hasKey("b")) color.b = colorData["b"].ToFloat();
	}

	if (_document.hasKey("layer")) layer = _document["layer"].ToInt();
}

void Font::Render()
{
	if (GetOwner())
	{
		SDL_FRect dstrect = { GetOwner()->GetTransform()->GetPosition().x, GetOwner()->GetTransform()->GetPosition().y, size, size };
		SDL_RenderCopyF(RenderSystem::Instance().GetRenderer(), message, NULL, &dstrect);
	}
}

void Font::CreateMessage()
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font->GetFontAsset(), text.c_str(), color);
	message = SDL_CreateTextureFromSurface(RenderSystem::Instance().GetRenderer(), surfaceMessage);
}