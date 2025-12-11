#pragma once
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "Object.h"

enum class WidgetVisibility
{
	Visable,
	Hide,
	Collapse,
	NotHitTestable
};

class Widget : public Object
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Widget, Object);
public:
	void Initialize() override;
	void Destroy() override;
	virtual void Update();
	virtual void Load(json::JSON& j);
	virtual void Start();

	void Render();

	glm::vec2 GetPosition();
	float GetRotation();

public:
	Widget* parent = nullptr;

protected:
	virtual void OnRender();

protected:
	std::list<Widget*> children;


	std::string name = "";
	glm::vec2 localPosition = {0,0};
	int layer = 0;
	float rotation = 0.0f;

	WidgetVisibility visibility = WidgetVisibility::Visable;

	friend class RenderSystem;


private:
	WidgetVisibility StringToVisibility(const std::string& str);
};

#endif


