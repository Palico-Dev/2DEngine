#pragma once

#ifndef _ANIMATEDSPRITE_H_
#define _ANIMATEDSPRITE_H_

#include "Component.h"
#include "Renderable.h"
#include "TextureAsset.h"

class AnimatedSprite : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(AnimatedSprite, Renderable);
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

protected:
	void Initialize() final;
	void Destroy() final;
	void Update() final;
	void Load(json::JSON& _document) final;
	void Render() final;
};

#endif

