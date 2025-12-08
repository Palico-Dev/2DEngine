#pragma once
#ifndef _UILABEL_H_
#define _UILABEL_H_

#include "Widget.h"

class FontAsset;

class UILabel : public Widget
{
	DECLARE_DYNAMIC_DERIVED_CLASS(UILabel, Widget);
public:
	void Initialize() override;
	void Destroy() override;
	void Update() override;
	void Load(json::JSON j) override;

	void SetText(const std::string& newText)
	{
		if (text != newText)
		{
			text = newText;
			isDirty = true;
		}
	}
	void SetColor(glm::vec4 newColor)
	{
		if (color != newColor)
		{
			color = newColor;
			isDirty = true;
		}
	}

protected:
	void OnRender() override;

protected:
	FontAsset* fontAsset;
	float size = 24;
	std::string text = "";
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	bool isDirty = true;
	SDL_Texture* texture = nullptr;
	int texW = 0;
	int texH = 0;
};

#endif


