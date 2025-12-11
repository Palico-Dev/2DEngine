#include "GameCore.h"
#include "HealthBar.h"
#include "TextureAsset.h"
#include "RenderSystem.h"
#include "AssetManager.h"
#include "FileManager.h"
#include "DataBindingRegistry.h"

IMPLEMENT_DYNAMIC_CLASS(HealthBar)

void HealthBar::Initialize()
{
	if (initialized)
		return;
	Widget::Initialize();
}

void HealthBar::Destroy()
{
	Widget::Destroy();
}

void HealthBar::Update()
{
	if (dataBinding != nullptr)
	{
		gameHealth = dataBinding();
	}

	Widget::Update();
}

void HealthBar::Load(json::JSON& j)
{
	Widget::Load(j);
	size = FileManager::JsonReadVec2(j, "size");

	image = AssetManager::Instance().GetAsset<TextureAsset>(FileManager::JsonReadString(j, "asset").c_str());

	std::string bindkey = FileManager::JsonReadString(j, "binding");
	if (bindkey != "")
	{
		dataBinding = DataBindingRegistry::Instance().GetIntBinding(GetHashCode(bindkey.c_str()));
	}
}

void HealthBar::OnRender()
{
	if (gameHealth <= 0) return; 
	if (!image) return;

	SDL_Texture* tex = image->GetTexture();
	if (!tex) return;


	float width = size.x; 
	float height = size.y;
	float padding = 5.0f;


	for (int i = 0; i < gameHealth; ++i)
	{
		SDL_FRect renderQuad;

		renderQuad.x = GetPosition().x + (i * (width + padding));
		renderQuad.y = GetPosition().y;
		renderQuad.w = width;
		renderQuad.h = height;

		SDL_RenderCopyExF(
			RenderSystem::Instance().GetRenderer(),
			tex,
			NULL,               
			&renderQuad,        
			0,     
			NULL,               
			SDL_FLIP_NONE      
		);
	}
}
