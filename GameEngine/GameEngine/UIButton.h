#pragma once
#ifndef _UIBUTTON_H_
#define _UIBUTTON_H_

#include "Widget.h"

class TextureAsset;

class UIButton : public Widget
{
	DECLARE_DYNAMIC_DERIVED_CLASS(UIButton,Widget);

public:
	enum class ButtonState{Normal,Hover,Pressed};

public:
	void Initialize() override;
	void Destroy() override;
	void Load(json::JSON& j) override;
	void Update() override;
	void OnRender() override;

public:
	bool IsMouseHover();

private:
	ButtonState state = ButtonState::Normal;
	std::function<void()> onClick = nullptr;

	TextureAsset* normalTexture = nullptr;
	TextureAsset* hoverTexture = nullptr;
	TextureAsset* pressedTexture = nullptr;
	glm::vec2 size = { 50,50 };

	glm::vec4 normalColor = { 0.7f,0.7f,0.7f,1.0f };
	glm::vec4 hoverColor = { 0.9f,0.9f,0.9f,1.0f };
	glm::vec4 pressColor = { 0.5f,0.5f,0.5f,1.0f };
};

#endif


