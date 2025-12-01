#pragma once

#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <list>
#include "SDL.h"
#include "SDL_image.h"

class Renderable;

class RenderSystem final
{
private:
	int totalLayers;
	int width;
	int height;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

public:
	SDL_Renderer* GetRenderer() { return renderer; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void AddRenderable(Renderable* _renderable);
	void RemoveRenderable(Renderable* _renderable);

private:
	void Initialize();
	void Update();
	void Destroy();

private:
	static RenderSystem* instance;
	std::list<Renderable*> renderables;

	DECLARE_SINGLETON(RenderSystem)

	friend class Engine;
};

#endif