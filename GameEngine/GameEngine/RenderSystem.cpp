#include "EngineCore.h"
#include "RenderSystem.h"
#include "Renderable.h"

void RenderSystem::Initialize()
{
	window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderSystem::Update()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// This is just a basic setup for the idea
	// Iterate through each layer to render
	//for (int i = 0; i < totalLayers; i++)
	//{
		for (auto& renderable : renderables)
		{
			// Checks if current renderable is on the particular layer
			//if (renderable->layer == i) // moved layer into the actual components- need a new way to get layer or figure out how to read layer in
			//{
				renderable->Render();
			//}
		}
	//}

	SDL_RenderPresent(renderer);
}

void RenderSystem::Destroy()
{
	renderables.clear();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void RenderSystem::AddRenderable(Renderable* _renderable)
{
	renderables.push_back(_renderable);
}

void RenderSystem::RemoveRenderable(Renderable* _renderable)
{
	renderables.remove(_renderable);
}
