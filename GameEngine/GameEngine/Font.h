#pragma once

#ifndef _FONT_H_
#define _FONT_H_

#include "Component.h"
#include "IRenderable.h"
#include <string>
#include "json.hpp"
#include "FontAsset.h"

class Font : public Component,public IRenderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Font, Component);

private:
	std::string fontName = "";
	std::string text = "";

	FontAsset* font;
	SDL_Color color = { 0, 0, 0 };
	SDL_Texture* message = nullptr;
	int size;

protected:
	void Initialize() final;
	void Destroy() final;
	void Update() final;
	void Load(json::JSON& _document) final;
	void Render() final;

	void SetText(std::string _text) { text = _text; }
	void CreateMessage();
};

#endif

