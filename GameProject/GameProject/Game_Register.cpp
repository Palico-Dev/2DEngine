#include "GameCore.h"
#include "SceneTestComponent1.h"

void Game_Register()
{
	REGISTER_TYPECLASS(SceneTestComponent1);
	REGISTER_TYPECLASS(ZombieAIComponent);
	REGISTER_TYPECLASS(ZombiePlayingComponent);
	REGISTER_TYPECLASS(ZombieFactoryComponent);
	REGISTER_TYPECLASS(AngelAIComponent);
	REGISTER_TYPECLASS(AngelPlayingComponent);
	REGISTER_TYPECLASS(AngelFactoryComponent);
}