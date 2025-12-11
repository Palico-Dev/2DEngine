#pragma once
#ifndef _UIIMAGE_H_
#define _UIIMAGE_H_

#include "Widget.h"

class TextureAsset;

class UIImage : public Widget
{
	DECLARE_DYNAMIC_DERIVED_CLASS(UIImage, Widget);

public:
	void Initialize() override;
	void Destroy() override;
	void Update() override;
	void Load(json::JSON& j) override;

protected:
	void OnRender() override;

private:
	TextureAsset* textureAsset;
	glm::vec2 size = { 100,100 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};


#endif


