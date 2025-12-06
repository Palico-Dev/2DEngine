#include "EngineCore.h"
#include "Object.h"
#include "Entity.h"
#include "Component.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Transform.h"
#include "Asset.h"
#include "TextureAsset.h"
#include "SoundAsset.h"
#include "FontAsset.h"
#include "PrefabAsset.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Widget.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UILabel.h"

void Engine_Register()
{
	REGISTER_TYPECLASS(Object);
	REGISTER_TYPECLASS(Entity);
	REGISTER_TYPECLASS(Asset);
	REGISTER_TYPECLASS(Component);
	REGISTER_TYPECLASS(Collider);
	REGISTER_TYPECLASS(BoxCollider);
	REGISTER_TYPECLASS(CircleCollider);
	REGISTER_TYPECLASS(Transform);
	REGISTER_TYPECLASS(SoundAsset);
	REGISTER_TYPECLASS(TextureAsset);
	REGISTER_TYPECLASS(FontAsset);
	REGISTER_TYPECLASS(PrefabAsset);
	REGISTER_TYPECLASS(Sprite);
	REGISTER_TYPECLASS(AnimatedSprite);
	REGISTER_TYPECLASS(Widget);
	REGISTER_TYPECLASS(UILabel);
	REGISTER_TYPECLASS(UIButton);
	REGISTER_TYPECLASS(UIImage);


}
