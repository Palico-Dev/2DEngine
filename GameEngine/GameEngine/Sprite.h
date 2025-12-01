#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Component.h"
#include "Renderable.h"
#include "TextureAsset.h"

class Sprite : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Sprite, Renderable);

private:
	std::string spriteName = "";

	TextureAsset* texture;
	SDL_Point size; // from transform

	// these are extra variables for being able to rotate and flip the sprite
	float angle = 0.0f; // get from transform
	SDL_FPoint* center = NULL;
	SDL_Rect* clip = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

protected:
	void Initialize() final;
	void Destroy() final;
	void Update() final;
	void Load(json::JSON& _document) final;
	void Render() final;

	int GetLayer() { return layer; }
	void SetLayer(int _layer) { layer = _layer; }
};

#endif

