#include "EngineCore.h"
#include "FontAsset.h"

IMPLEMENT_DYNAMIC_CLASS(FontAsset)

void FontAsset::Destroy()
{
    TTF_CloseFont(font);
    TTF_Quit();
    font = nullptr;
}

void FontAsset::Init()
{
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
    }
}

void FontAsset::LoadFont(int _size)
{
    font = TTF_OpenFont(path.c_str(), _size);
    if (font == NULL) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
    }
}

void FontAsset::Load()
{
    Init();
    LoadFont(fontSize);    
}

void FontAsset::SetFontSize(int _size)
{
    if (fontSize == _size) return;
    Init();

    TTF_CloseFont(font);
    fontSize = _size;

    LoadFont(fontSize);
}
