#pragma once
#include "Component.h"
#include "Renderable.h"

class Gizmo : public Renderable
{
private:
	std::string gizmoName;
	SDL_Texture* texture;
	int width;
	int height;
	float angle;
	SDL_Point* center = NULL;
	SDL_Rect* clip = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Point size;

protected:
	void Initialize() final;
	void Destroy() final;
	void Update() final;
	void Render() final;
};

