#pragma once

#ifndef _ANIMATEDSPRITE_H_
#define _ANIMATEDSPRITE_H_

#include "Component.h"
#include "IRenderable.h"
#include "TextureAsset.h"

class AnimatedSprite : public Component,public IRenderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(AnimatedSprite, Component);

public:
	void Initialize() final;
	void Destroy() final;
	void Update() final;
	void Load(json::JSON& _document) final;
	Component* Clone() override;
	void Render() final;
private:
	std::string spriteName = "";

	TextureAsset* texture;
	SDL_Point size; // from transform
	float speed = 0.0;
	int row = 1;
	int curFrame = -1;
	int frameCount = 0;

	int width = 0;
	int height = 0;

	// these are extra variables for being able to rotate and flip the sprite
	float angle = 0.0f;
	SDL_FPoint* center = NULL;
	SDL_Rect* clip = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;


};

#endif

