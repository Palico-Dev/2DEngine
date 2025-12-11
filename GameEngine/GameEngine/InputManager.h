#pragma once
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <SDL.h>
#include <unordered_map>
#include <unordered_set>
#include "Event.h"

// use char as a bitmask (since sdl mouse buttons are 1-3) without the overhead of an std set
typedef unsigned char btn_bitmask;
#define BTN_GET(mask, which) mask & (1 << which)
#define BTN_SET(mask, which) mask = mask | (1 << which)
#define BTN_ERASE(mask, which) mask = mask & ~(1 << which)

class InputManager final
{
	std::unordered_set<SDL_Keycode> heldKeys;
	std::unordered_set<SDL_Keycode> pressedKeys;
	std::unordered_set<SDL_Keycode> releasedKeys;
	btn_bitmask heldMouse;
	btn_bitmask pressedMouse;
	btn_bitmask releasedMouse;

	std::unordered_map<std::string, std::unordered_set<SDL_Keycode>> actionMap;
	std::unordered_set<std::string> disabledActions;  // set by the toggle function
	SDL_Point currMousePos{ 0, 0 };
	SDL_Point lastMousePos{ 0, 0 };
	SDL_Point difference{ 0, 0 };  // mouse delta
	float scrollY = 0;  // the current vertical scroll amount

public:
	void Initialize();
	void Update();
	void Destroy();

	// key queries
	bool GetKey(SDL_KeyCode key) { return heldKeys.count(key) > 0; }
	bool GetKeyPressed(SDL_KeyCode key) { return pressedKeys.count(key) > 0; }
	bool GetKeyReleased(SDL_KeyCode key) { return releasedKeys.count(key) > 0; }
	int GetAxis(SDL_KeyCode negative, SDL_KeyCode positive) { return (int)GetKey(positive) - (int)GetKey(negative); }

	// mouse queries
	bool GetMouse(int button) { return BTN_GET(heldMouse, button); }
	bool GetMousePressed(int button) { return BTN_GET(pressedMouse, button); }
	bool GetMouseReleased(int button) { return BTN_GET(releasedMouse, button); }
	SDL_Point GetMousePosition() { return currMousePos; }
	SDL_Point GetMouseDelta() { return difference; }
	float GetScrollAmount() { return scrollY; }  // positive up

	bool IsMouseDown(int button)
	{
		int x, y; 

		Uint32 state = SDL_GetMouseState(&x, &y);

		return (state & SDL_BUTTON(button));
	}

	void BindAction(std::string action, SDL_KeyCode key) { actionMap[action].insert(key); }
	void UnbindAction(std::string action, SDL_KeyCode key) { actionMap[action].erase(key); }
	void UnbindAction(std::string action) { actionMap.erase(action); }
	void ToggleAction(std::string, bool);
	bool IsToggled(std::string action) { return disabledActions.count(action) == 0; }
	bool GetAction(std::string);
	bool GetActionPressed(std::string);
	bool GetActionReleased(std::string);
	int GetAxis(std::string negative, std::string positive) { return (int)GetAction(positive) - (int)GetAction(negative); }
	std::unordered_set<SDL_Keycode> GetBinds(std::string action) { return actionMap[action]; }
	bool IsBound(std::string action, SDL_KeyCode key) { return actionMap[action].count(key) > 0; }

	const Event<SDL_Keycode> OnKeyPress;
	const Event<SDL_Keycode> OnKeyRelease;
	const Event<int> OnMousePress;
	const Event<int> OnMouseRelease;
	const Event<float> OnMouseScroll;
	const Event<SDL_Point, SDL_Point> OnMouseMove;
	const Event<std::string> OnActionPress;
	const Event<std::string> OnActionRelease;

	DECLARE_SINGLETON(InputManager)
};

#endif //_INPUTMANAGER_H_