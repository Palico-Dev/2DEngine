// Written by Andy & Anthony

#include "EngineCore.h"
#include "InputManager.h"
#include "Engine.h"

void InputManager::ToggleAction(std::string action, bool enabled)
{
	if (!enabled) {
		// disable the action
		disabledActions.insert(action);
	}
	else {
		// reenable the action
		disabledActions.erase(action);
	}
}

bool InputManager::GetAction(std::string action)
{
	if (!IsToggled(action)) {
		return false;
	}
	for (const auto& key : actionMap[action]) {
		if (GetKey((SDL_KeyCode)key))
			return true;
	}
	return false;
}

bool InputManager::GetActionPressed(std::string action)
{
	if (!IsToggled(action)) {
		return false;
	}
	for (const auto& key : actionMap[action]) {
		if (GetKeyPressed((SDL_KeyCode)key))
			return true;
	}
	return false;
}

bool InputManager::GetActionReleased(std::string action)
{
	if (!IsToggled(action)) {
		return false;
	}
	for (const auto& key : actionMap[action]) {
		if (GetKeyReleased((SDL_KeyCode)key))
			return true;
	}
	return false;
}

void InputManager::Initialize() {
	SDL_GetMouseState(&currMousePos.x, &currMousePos.y);
	lastMousePos = currMousePos;
}

void InputManager::Update() {
	SDL_Event event;
	SDL_KeyboardEvent key;
	SDL_MouseMotionEvent motion;
	SDL_MouseButtonEvent button;
	SDL_MouseWheelEvent wheel;

	pressedKeys.clear();
	releasedKeys.clear();
	pressedMouse = 0;
	releasedMouse = 0;

	while (SDL_PollEvent(&event)) {
		key = event.key;
		motion = event.motion;
		button = event.button;
		wheel = event.wheel;
		
		switch (event.type) {
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
				Engine::Instance().quit = true;
			}
			break;
	
		case SDL_KEYDOWN:  // Detect when a key is pressed down
			if (key.repeat != 0) break;

			heldKeys.insert(key.keysym.sym);
			pressedKeys.insert(key.keysym.sym);
			OnKeyPress.Fire(key.keysym.sym);

			// detect actions that are pressed down
			for (auto& it : actionMap) {
				if (GetActionPressed(it.first)) {
					OnActionPress.Fire(it.first);
				}
			}

			break;

		case SDL_KEYUP:  // Detect when a key is released
			heldKeys.erase(key.keysym.sym);
			releasedKeys.insert(key.keysym.sym);
			OnKeyRelease.Fire(key.keysym.sym);

			// detect actions that are released
			for (auto& it : actionMap) {
				if (GetActionReleased(it.first)) {
					OnActionRelease.Fire(it.first);
				}
			}

			break;

		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&currMousePos.x, &currMousePos.y);
			difference = { currMousePos.x - lastMousePos.x, currMousePos.y - lastMousePos.y };
			lastMousePos = currMousePos;
			OnMouseMove.Fire(currMousePos, difference);

			break;

		case SDL_MOUSEBUTTONDOWN: // Detect when a mouse button is pressed down
			BTN_SET(heldMouse, button.button);
			BTN_SET(pressedMouse, button.button);
			OnMousePress.Fire(button.button);

			break;

		case SDL_MOUSEBUTTONUP: // Detect when a mouse button is released
			BTN_ERASE(heldMouse, button.button);
			BTN_SET(releasedMouse, button.button);
			OnMouseRelease.Fire(button.button);

			break;

		case SDL_MOUSEWHEEL:
			scrollY = wheel.preciseY;
			OnMouseScroll.Fire(scrollY);

			break;
		}
	}
}

void InputManager::Destroy() {

}