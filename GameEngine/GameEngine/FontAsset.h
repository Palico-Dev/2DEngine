#ifndef _FONTASSET_H_
#define _FONTASSET_H_

#include "Asset.h"
class FontAsset : public Asset
{
	DECLARE_DYNAMIC_DERIVED_CLASS(FontAsset, Asset)

public:
	TTF_Font* GetFontAsset(int _size) { return fontMap[_size]; }
	void SetFontSize(int _size);

private:
	void Init();
	void Load(json::JSON j) override;
	void Destroy() override;
	void LoadFont(json::JSON j, int _size);

private:
	std::map<int,TTF_Font*> fontMap{};
	int fontSize = 24;
	json::JSON path;

};

#endif
