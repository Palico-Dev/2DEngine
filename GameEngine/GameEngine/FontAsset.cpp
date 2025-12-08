#include "EngineCore.h"
#include "FontAsset.h"

IMPLEMENT_DYNAMIC_CLASS(FontAsset)

void FontAsset::Destroy()
{
    for (auto& pair : fontMap)
    {
		TTF_CloseFont(pair.second);

        pair.second = nullptr;
    }
    TTF_Quit();

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

	TTF_Font* font = TTF_OpenFont(path.generic_string().c_str(), _size);
	if (font == NULL)
	{
		std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
		TTF_Quit();
	}
    fontMap.emplace(_size, font);
}

void FontAsset::Load(json::JSON j)
{
    Init();
    LoadFont(j,fontSize);   
    path = j;
}

void FontAsset::SetFontSize(int _size)
{
    if (fontSize == _size) return;
    
    LoadFont(path,_size);
    fontSize = _size;

    //LoadFont(fontSize);
}
