#ifndef _TEXTUREASSET_H_
#define _TEXTUREASSET_H_

#include "Asset.h"

class TextureAsset : public Asset
{
	DECLARE_DYNAMIC_DERIVED_CLASS(TextureAsset, Asset)

public:
	SDL_Texture* GetTexture() { return texture; }

private:
	SDL_Texture* texture{};
	void Load(json::JSON j, std::string& _fileName) override;
	void Destroy() override;
};

#endif
