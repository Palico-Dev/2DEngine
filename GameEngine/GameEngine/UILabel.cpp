#include "EngineCore.h"
#include "UILabel.h"
#include "FileManager.h"
#include "FontAsset.h"
#include "AssetManager.h"
#include "RenderSystem.h"

IMPLEMENT_DYNAMIC_CLASS(UILabel)

void UILabel::Initialize()
{
	if (initialized)
		return;
	Widget::Initialize();
}

void UILabel::Destroy()
{
	Widget::Destroy();
}

void UILabel::Update()
{
	Widget::Update();
}
void UILabel::Load(json::JSON j)
{
	Widget::Load(j);

	size = FileManager::JsonReadInt(j, "size");
	color = FileManager::JsonReadColor(j, "color");
	text = FileManager::JsonReadString(j, "text");
	fontAsset = (FontAsset*)AssetManager::Instance().GetAsset(FileManager::JsonReadString(j, "font").c_str());
	fontAsset->SetFontSize(size);
}

void UILabel::OnRender()
{
	if (isDirty && fontAsset->GetFontAsset() != nullptr && !text.empty())
	{
		if (texture) SDL_DestroyTexture(texture);

		Uint8 r = static_cast<Uint8>(color.r * 255.0f);
		Uint8 g = static_cast<Uint8>(color.g * 255.0f);
		Uint8 b = static_cast<Uint8>(color.b * 255.0f);
		Uint8 a = static_cast<Uint8>(color.a * 255.0f);
		SDL_Color c = { r,g,b,a };

		TTF_Font* font = fontAsset->GetFontAsset();

		SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), c);

		if (surface)
		{
			texture = SDL_CreateTextureFromSurface(RenderSystem::Instance().GetRenderer(), surface);

			texW = surface->w;
			texH = surface->h;

			SDL_FreeSurface(surface);
		}
		isDirty = false;
	}

	if (texture)
	{
		float parentRad = parent->GetRotation() * (M_PI / 180.0f);

		float rotX = (localPosition.x * cos(parentRad)) - (localPosition.y * sin(parentRad));
		float rotY = (localPosition.x * sin(parentRad)) + (localPosition.y * cos(parentRad));

		float finalX = parent->GetPosition().x + rotX;
		float finalY = parent->GetPosition().y + rotY;

		SDL_FRect dstRect = {
			finalX,
			finalY,
			static_cast<float>(texW),
			static_cast<float>(texH)
		};

		double finalRotation = GetRotation();

		SDL_RenderCopyExF(
			RenderSystem::Instance().GetRenderer(),
			texture,
			NULL,
			&dstRect,
			finalRotation,
			NULL,
			SDL_FLIP_NONE
		);
	}
}
