#pragma once
#ifndef _UISYSTEM_H_
#define _UISYSTEM_H_

class Widget;

class UISystem
{
	DECLARE_SINGLETON(UISystem);

public:
	Widget* GetRoot() { return root; }
	void Render();
	void Load(json::JSON j);

private:
	void Initialize();
	void Update();
	void Destroy();




private:
	Widget* root = nullptr;

	friend class Engine;
	friend class RenderSystem;
};

#endif


