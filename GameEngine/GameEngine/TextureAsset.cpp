#include "EngineCore.h"
#include "TextureAsset.h"
#include "RenderSystem.h"

IMPLEMENT_DYNAMIC_CLASS(TextureAsset)

void TextureAsset::Load(json::JSON j)
{
	fs::path path;
	if (FileManager::JsonReadString(j, "Location")=="Engine")
	{
		path = FileManager::GetEngineAssetPath();
	}
	else
	{
		path = FileManager::GetAssetPath();
	}
	path = path / FileManager::JsonReadString(j, "Asset");
	SDL_Surface* surface = IMG_Load(path.generic_string().c_str());
	if (surface == nullptr)
	{
		Debug::Warning("Cannot find Texture!" + path.generic_string());
	}

	SDL_Renderer* renderer = RenderSystem::Instance().GetRenderer();
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    if (!texture) {
		Debug::Warning("Cannot Create Texture!" + path.generic_string());
    }
}

void TextureAsset::Destroy()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
