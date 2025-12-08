#include "EngineCore.h"
#include "UISystem.h"
#include "Widget.h"

void UISystem::Initialize()
{
	if (root == nullptr)
	{
		root = (Widget*)CreateObject("Widget");
	}
}

void UISystem::Update()
{
	root->Update();
}

void UISystem::Destroy()
{
	root->Destroy();
}

void UISystem::Start()
{
	root->Start();
}

void UISystem::Load(json::JSON j)
{
	if (j.hasKey("ui"))
	{
		root = (Widget*)CreateObject("Widget");
		root->Load(j["ui"]);
	}
}

void UISystem::Render()
{
	root->Render();
}
