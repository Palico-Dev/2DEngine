#include "EngineCore.h"
#include "TextureAsset.h"
#include "RenderSystem.h"

IMPLEMENT_DYNAMIC_CLASS(TextureAsset)

void TextureAsset::Load()
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		std::stringstream msg_s;
		msg_s << "Cannot find texture - " << __FILE__ << ", " << __LINE__;
		throw std::exception(msg_s.str().c_str());
	}

	SDL_Renderer* renderer = RenderSystem::Instance().GetRenderer();
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    if (!m_texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }
}

void TextureAsset::Destroy()
{
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}
