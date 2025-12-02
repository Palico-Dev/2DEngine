#include "EngineCore.h"
#include "TextureAsset.h"
#include "RenderSystem.h"

IMPLEMENT_DYNAMIC_CLASS(TextureAsset)

void TextureAsset::Load(json::JSON j)
{
	std::string path = FileManager::JsonReadString(j, "Asset");
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		Debug::Warning("Cannot find Texture!" + path);
	}

	SDL_Renderer* renderer = RenderSystem::Instance().GetRenderer();
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    if (!texture) {
		Debug::Warning("Cannot Create Texture!" + path);
    }
}

void TextureAsset::Destroy()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
