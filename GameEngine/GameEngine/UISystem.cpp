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

Widget* UISystem::FindWidgetByName(const std::string& name)
{
	if (root->name == name)
	{
		return root;
	}
	else
	{
		std::list<Widget*> searchList = root->children;
		while (!searchList.empty())
		{
			Widget* current = searchList.front();
			searchList.pop_front();
			if (current->name == name)
			{
				return current;
			}
			for (auto& w : current->children)
			{
				searchList.push_back(w);
			}
		}
	}
}

void UISystem::Render()
{
	root->Render();
}
