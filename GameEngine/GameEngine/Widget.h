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

	virtual void Render();

private:
	std::list<Widget*> children;
	Widget* parent = nullptr;

	glm::vec2 localPosition = {0,0};
	glm::vec2 size = {50,50};

	WidgetVisibility visibility = WidgetVisibility::Visable;

	friend class RenderSystem;

};

#endif


