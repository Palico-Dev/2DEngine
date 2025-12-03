#include "EngineCore.h"
#include "RenderSystem.h"
#include "IRenderable.h"
#include "Engine.h"
#include "FileManager.h"

void RenderSystem::Initialize()
{
	int w = 1280;
	int h = 720;
	std::string windowName;

	json::JSON gamesetting = Engine::Instance().GetGameSettings();
	json::JSON renderSetting = FileManager::JsonReadJson(gamesetting, "RenderSystem");

	int width = FileManager::JsonReadInt(renderSetting, "Width");
	if (width != -1)
		w = width;

	int height = FileManager::JsonReadInt(renderSetting, "Height");
	if (height != -1)
		h = height;

	std::string s = FileManager::JsonReadString(renderSetting, "Name");
	if (s != "")
		windowName = s;

	bool fullscreen = FileManager::JsonReadBool(renderSetting, "FullScreen");

	if(fullscreen)
		window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_FULLSCREEN);
	else
		window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

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

void RenderSystem::AddRenderable(IRenderable* _renderable)
{
	renderables.push_back(_renderable);
}

void RenderSystem::RemoveRenderable(IRenderable* _renderable)
{
	renderables.remove(_renderable);
}
