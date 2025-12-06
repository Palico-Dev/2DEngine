#include "EngineCore.h"
#include "Widget.h"
#include "FileManager.h"

IMPLEMENT_DYNAMIC_CLASS(Widget);

void Widget::Initialize()
{
	if (initialized)
		return;
	Object::Initialize();


}

void Widget::Destroy()
{
	for (auto& w:children)
	{
		w->Destroy();
		delete w;
	}
	children.clear();
}

void Widget::Update()
{

}

void Widget::Load(json::JSON j)
{
	name = FileManager::JsonReadString(j, "name");
	localPosition = FileManager::JsonReadVec2(j, "localPosition");
	layer = FileManager::JsonReadInt(j, "layer");
	rotation = FileManager::JsonReadFloat(j, "rotation");
	visibility = StringToVisibility(FileManager::JsonReadString(j, "visibility"));

	if (j.hasKey("children"))
	{
		json::JSON childrenJson = j.at("children");
		for (auto& w : childrenJson.ArrayRange())
		{
			std::string type = FileManager::JsonReadString(w,"type");
			Widget* newWidget = (Widget*)CreateObject(type.c_str());
			children.push_back(newWidget);
			newWidget->parent = this;
			newWidget->Load(w);
		}
	}
}

void Widget::Render()
{
	if (visibility == WidgetVisibility::Collapse || visibility == WidgetVisibility::Hide)
		return;
	OnRender();
	for (auto& w : children)
	{
		w->Render();
	}
}

glm::vec2 Widget::GetPosition()
{
	if (parent != nullptr)
	{
		return localPosition + parent->GetPosition();
	}
	else
	{
		return localPosition;
	}
}

float Widget::GetRotation()
{
	if (parent != nullptr)
	{
		return rotation + parent->GetRotation();
	}
	else
	{
		return rotation;
	}
}

void Widget::OnRender()
{

}

WidgetVisibility Widget::StringToVisibility(const std::string& str)
{
	static const std::unordered_map<std::string, WidgetVisibility> map = {
		{"Visible", WidgetVisibility::Visable},
		{"Hide", WidgetVisibility::Hide},
		{"Collapse", WidgetVisibility::Collapse},
		{"NotHitTestable", WidgetVisibility::NotHitTestable}
	};

	auto it = map.find(str);
	if (it != map.end())
	{
		return it->second;
	}

	return WidgetVisibility::Visable;
}
