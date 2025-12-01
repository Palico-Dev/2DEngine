#ifndef _SOUNDASSET_H_
#define _SOUNDASSET_H_

#include "Asset.h"
class SoundAsset: public Asset
{
	DECLARE_DYNAMIC_DERIVED_CLASS(SoundAsset, Asset)

public:
	Mix_Chunk* GetSoundAsset() { return sound; }
	void PlaySoundAsset();

private:
	Mix_Chunk* sound{};
	void Init();
	void Load() override;
	void Destroy() override;
};

#endif
