#ifndef _TEXTUREASSET_H_
#define _TEXTUREASSET_H_

#include "Asset.h"

class TextureAsset : public Asset
{
	DECLARE_DYNAMIC_DERIVED_CLASS(TextureAsset, Asset)

public:
	SDL_Texture* GetTexture() { return m_texture; }

private:
	SDL_Texture* m_texture{};
	void Load() override;
	void Destroy() override;
};

#endif
