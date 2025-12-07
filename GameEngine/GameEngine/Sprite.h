#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Component.h"
#include "IRenderable.h"
#include "TextureAsset.h"

class Sprite : public Component, public IRenderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Sprite, Component);
public:
	void SetColor(glm::vec4 c);

protected:
	void Initialize() final;
	void Destroy() final;
	void Update() final;
	void Load(json::JSON& _document) final;
	Component* Clone() override;
	void Render() final;

	int GetLayer() { return layer; }
	void SetLayer(int _layer) { layer = _layer; }

private:
	std::string spriteName = "";

	TextureAsset* textureAsset;
	glm::vec2 size = { 100,100 };
	glm::vec2 offset = { 0,0 };
	float rotation = 0.0f;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

#endif

