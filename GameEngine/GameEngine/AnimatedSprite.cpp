#include "EngineCore.h"
#include "AnimatedSprite.h"
#include "Entity.h"
#include "Transform.h"
#include "RenderSystem.h"
#include "AssetManager.h"

static SDL_Rect tempClip;

IMPLEMENT_DYNAMIC_CLASS(AnimatedSprite);

void AnimatedSprite::Initialize()
{
	Component::Initialize();

}

void AnimatedSprite::Destroy()
{
	Component::Destroy();
	RenderSystem::Instance().RemoveRenderable(this);
	// Cleanup of TextureAsset will be handled by AssetManager
	texture = nullptr;
	if (center != NULL) delete center;
	if (clip != NULL) delete clip;
}

void AnimatedSprite::Update()
{
	Component::Update();

	curFrame = (SDL_GetTicks() / (int)speed) % frameCount; // updating the current frame based on speed
}

// TODO: edit this load function to include AssetManager stuff
void AnimatedSprite::Load(json::JSON& _document)
{
	Component::Load(_document);
	if (_document.hasKey("spriteName"))
	{
		Component::Load(_document);
		if (_document.hasKey("name")) spriteName = _document["spriteName"].ToString();

		//if (_document.hasKey("asset")) texture = AssetManager::Instance().GetAsset<TextureAsset>(_document["asset"].ToString().c_str());

		if (_document.hasKey("animationSpeed")) speed = _document["animationSpeed"].ToFloat();

		if (_document.hasKey("layer")) layer = _document["layer"].ToInt();

		RenderSystem::Instance().AddRenderable(this);
	}
}

void AnimatedSprite::Render()
{
	if (GetOwner())
	{
		//TODO: add being able to change what frame we're on at a given speed
		SDL_QueryTexture(texture->GetTexture(), NULL, NULL, &width, &height); // query the texture to retrieve the width and height
		clip = &tempClip; // using a temporary static clip to avoid memory issues
		*clip = { width * curFrame, height * (row - 1), width, height }; // need to get the width and height from TextureAsset

		//Set rendering space and render to screen
		SDL_FRect renderQuad = { GetTransform()->GetPosition().x, GetTransform()->GetPosition().y, size.x, size.y };

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