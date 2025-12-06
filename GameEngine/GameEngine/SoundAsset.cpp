#include "EngineCore.h"
#include "SoundAsset.h"

IMPLEMENT_DYNAMIC_CLASS(SoundAsset)

void SoundAsset::Init()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_mixer could not initialize! Mixer_Error: " << Mix_GetError() << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mixer could not open audio! Mixer_Error: " << Mix_GetError() << std::endl;
    }
}

void SoundAsset::Load(json::JSON j)
{
    Init();
    std::string path = FileManager::JsonReadString(j, "Asset");
    sound = Mix_LoadWAV(path.c_str());
    if (!sound) {
        std::cerr << "Cannot load the .wav file! Mixer_Error: " << Mix_GetError() << std::endl;
    }
}

void SoundAsset::PlaySoundAsset()
{
    Mix_PlayChannel(-1, sound, 0);
}

void SoundAsset::Destroy()
{
    if (sound) {
        Mix_FreeChunk(sound);
        sound = nullptr;
    }

    Mix_CloseAudio();
}
