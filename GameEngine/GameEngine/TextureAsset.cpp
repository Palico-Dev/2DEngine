#include "EngineCore.h"
#include "TextureAsset.h"
#include "RenderSystem.h"

IMPLEMENT_DYNAMIC_CLASS(TextureAsset)

void TextureAsset::Load(json::JSON j)
{
	fs::path path = FileManager::GetAssetPath(j);

	SDL_Surface* surface = IMG_Load(path.generic_string().c_str());
	if (surface == nullptr)
	{
		Debug::Warning("Cannot find Texture!" + path.generic_string());
		return;
	}

	SDL_Renderer* renderer = RenderSystem::Instance().GetRenderer();
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    if (!texture) {
		Debug::Warning("Cannot Create Texture!" + path.generic_string());
		return;
    }

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void TextureAsset::Destroy()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
