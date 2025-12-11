#include "EngineCore.h"
#include "UIButton.h"
#include "FileManager.h"
#include "AssetManager.h"
#include "TextureAsset.h"
#include "DataBindingRegistry.h"
#include "InputManager.h"
#include "RenderSystem.h"

IMPLEMENT_DYNAMIC_CLASS(UIButton);

void UIButton::Initialize()
{
	Widget::Initialize();
}

void UIButton::Destroy()
{
	Widget::Destroy();
}

void UIButton::Load(json::JSON& j)
{
	Widget::Load(j);
	normalTexture = AssetManager::Instance().GetAsset<TextureAsset>(FileManager::JsonReadString(j, "normalTexture"));
	hoverTexture = AssetManager::Instance().GetAsset<TextureAsset>(FileManager::JsonReadString(j, "hoverTexture"));
	pressedTexture = AssetManager::Instance().GetAsset<TextureAsset>(FileManager::JsonReadString(j, "pressedTexture"));

	size = FileManager::JsonReadVec2(j, "size");
	onClick = DataBindingRegistry::Instance().GetActionBinding(GetHashCode(FileManager::JsonReadString(j, "onClick").c_str()));

}

void UIButton::Update()
{
	bool isHovering = IsMouseHover();

	bool isMouseDown = InputManager::Instance().IsMouseDown(SDL_BUTTON_LEFT);
	if (isHovering)
	{
		if (isMouseDown)
		{
			state = ButtonState::Pressed;
		}
		else
		{
			if (state == ButtonState::Pressed)
			{
				if (onClick) 
					onClick(); 
			}
			state = ButtonState::Hover;
		}
	}
	else
	{
		state = ButtonState::Normal;
	}

	Widget::Update();
}

void UIButton::OnRender()
{
	TextureAsset* activeAsset = normalTexture;
	glm::vec4 color = normalColor;

	if (state == ButtonState::Hover && hoverTexture)
	{
		activeAsset = hoverTexture;
		color = hoverColor;
	}
	else if (state == ButtonState::Pressed && pressedTexture)
	{
		activeAsset = pressedTexture;
		color = pressColor;
	}
	if (!activeAsset) return;
	SDL_Texture* tex = activeAsset->GetTexture();
	if (!tex) return;


	float renderW = size.x;
	float renderH = size.y;

	glm::vec2 parentPos = parent->GetPosition();
	float ownerAngleDeg = parent->GetRotation();

	float angleRad = ownerAngleDeg * (M_PI / 180.0f);

	float rotatedOffsetX = (localPosition.x * std::cos(angleRad)) - (localPosition.y * std::sin(angleRad));
	float rotatedOffsetY = (localPosition.x * std::sin(angleRad)) + (localPosition.y * std::cos(angleRad));

	float finalCenterX = parentPos.x + rotatedOffsetX;
	float finalCenterY = parentPos.y + rotatedOffsetY;

	SDL_FRect renderQuad = {
		finalCenterX - (renderW * 0.5f),
		finalCenterY - (renderH * 0.5f),
		renderW,
		renderH
	};

	float finalRenderAngle = ownerAngleDeg + rotation;

	Uint8 r = static_cast<Uint8>(color.r * 255.0f);
	Uint8 g = static_cast<Uint8>(color.g * 255.0f);
	Uint8 b = static_cast<Uint8>(color.b * 255.0f);
	Uint8 a = static_cast<Uint8>(color.a * 255.0f);

	SDL_SetTextureColorMod(tex, r, g, b);
	SDL_SetTextureAlphaMod(tex, a);

	SDL_RenderCopyExF(
		RenderSystem::Instance().GetRenderer(),
		tex,
		NULL,              
		&renderQuad,        
		finalRenderAngle,   
		NULL,               
		SDL_FLIP_NONE              
	);

	SDL_SetTextureColorMod(tex, 255, 255, 255);
	SDL_SetTextureAlphaMod(tex, 255);
}

bool UIButton::IsMouseHover()
{
	glm::vec2 mousePos = { InputManager::Instance().GetMousePosition().x, InputManager::Instance().GetMousePosition().y };
	
	return (mousePos.x >= GetPosition().x - 0.5f*size.x && mousePos.x <= GetPosition().x + 0.5f * size.x &&
		mousePos.y >= GetPosition().y - 0.5f*size.y && mousePos.y <= GetPosition().y + 0.5f * size.y);
}
