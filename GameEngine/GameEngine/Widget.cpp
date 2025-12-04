#include "EngineCore.h"
#include "Widget.h"

IMPLEMENT_DYNAMIC_CLASS(Widget);

void Widget::Initialize()
{
	if (initialized)
		return;
	Object::Initialize();


}

void Widget::Destroy()
{

}

void Widget::Render()
{

}
