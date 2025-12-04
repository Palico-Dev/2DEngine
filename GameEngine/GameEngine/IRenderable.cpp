#include "EngineCore.h"
#include "IRenderable.h"
#include "RenderSystem.h"

IRenderable::IRenderable()
{
	//RenderSystem::Instance().AddRenderable(this);
}

IRenderable::~IRenderable()
{
	OnDisable();
}

void IRenderable::OnEnable()
{
	if (!enabled)
	{
		RenderSystem::Instance().AddRenderable(this,layer);
		enabled = true;
	}
}

void IRenderable::OnDisable()
{
	if (enabled)
	{
		RenderSystem::Instance().RemoveRenderable(this, layer);
		enabled = false;
	}
}
