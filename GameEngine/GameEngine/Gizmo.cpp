#include "EngineCore.h"
#include "Gizmo.h"
#include "Entity.h"
#include "RenderSystem.h"
#include <iostream>
#include <sstream>

void Gizmo::Initialize()
{
	Component::Initialize();
}

void Gizmo::Destroy()
{
	Component::Destroy();
	RenderSystem::Instance().RemoveRenderable(this);
}

void Gizmo::Update()
{
	Component::Update();
}

void Gizmo::Render()
{
	if (GetOwner())
	{
		SDL_Rect outlineRect = { RenderSystem::Instance().GetWidth() / 6, RenderSystem::Instance().GetHeight() / 6,
			RenderSystem::Instance().GetWidth() * 2 / 3, RenderSystem::Instance().GetHeight() * 2 / 3 };
		SDL_SetRenderDrawColor(RenderSystem::Instance().GetRenderer(), 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(RenderSystem::Instance().GetRenderer(), &outlineRect);
	}
}