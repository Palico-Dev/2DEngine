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
    }
}

void FontAsset::LoadFont(json::JSON j, int _size)
{
    fs::path path = FileManager::GetAssetPath(j);

	font = TTF_OpenFont(path.generic_string().c_str(), _size);
	if (font == NULL)
	{
		std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
		TTF_Quit();
	}
}

void FontAsset::Load(json::JSON j)
{
    Init();
    LoadFont(j,fontSize);    
}

void FontAsset::SetFontSize(int _size)
{
    if (fontSize == _size) return;
    Init();

    TTF_CloseFont(font);
    fontSize = _size;

    //LoadFont(fontSize);
}
