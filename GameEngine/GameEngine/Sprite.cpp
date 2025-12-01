#include "EngineCore.h"
#include "Sprite.h"
#include "Entity.h"
#include "RenderSystem.h"
#include "Transform.h"
#include "AssetManager.h"

IMPLEMENT_DYNAMIC_CLASS(Sprite);

void Sprite::Initialize()
{
	Component::Initialize();
}

void Sprite::Destroy()
{
	Component::Destroy();
	RenderSystem::Instance().RemoveRenderable(this);
	// Cleanup of TextureAsset will be handled by AssetManager
	texture = nullptr;
	if (center != NULL) delete center;
	if (clip != NULL) delete clip;
}

void Sprite::Update()
{
	Component::Update();
}

// TODO: edit this load function to include AssetManager stuff
void Sprite::Load(json::JSON& _document)
{
	Component::Load(_document);
	if (_document.hasKey("name")) spriteName = _document["spriteName"].ToString();
	
	if (_document.hasKey("asset")) texture = AssetManager::Instance().GetAsset<TextureAsset>(_document["asset"].ToString().c_str());
	
	if (_document.hasKey("layer")) layer = _document["layer"].ToInt();
	
	RenderSystem::Instance().AddRenderable(this);
}

void Sprite::Render()
{
	if (GetOwner())
	{
		//Set rendering space and render to screen
		SDL_FRect renderQuad = { GetTransform()->GetPosition().x, GetTransform()->GetPosition().y, size.x, size.y};

		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyExF(RenderSystem::Instance().GetRenderer(), texture->GetTexture(), clip, &renderQuad, angle, center, flip);
	}
}