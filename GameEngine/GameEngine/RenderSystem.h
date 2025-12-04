#pragma once

#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <list>
#include "SDL.h"
#include "SDL_image.h"

class IRenderable;

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

	void AddRenderable(IRenderable* _renderable, int layer = 0);
	void RemoveRenderable(IRenderable* _renderable, int layer = 0);
	void UpdateLayer(IRenderable* _renderable, int oldLayer, int newLayer);

private:
	void Initialize();
	void Update();
	void Destroy();

private:
	static RenderSystem* instance;
	std::map<int,std::list<IRenderable*>> renderableMap;

	DECLARE_SINGLETON(RenderSystem)

	friend class Engine;
};

#endif