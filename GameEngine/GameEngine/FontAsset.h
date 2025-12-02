#ifndef _FONTASSET_H_
#define _FONTASSET_H_

#include "Asset.h"
class FontAsset : public Asset
{
	DECLARE_DYNAMIC_DERIVED_CLASS(FontAsset, Asset)

public:
	TTF_Font* GetFontAsset() { return font; }
	int GetFontSize() { return fontSize; }
	void SetFontSize(int _size);

private:
	TTF_Font* font{};
	int fontSize = 24;
	void Init();
	void Load(json::JSON j) override;
	void Destroy() override;
	void LoadFont(json::JSON j, int _size);
};

#endif
