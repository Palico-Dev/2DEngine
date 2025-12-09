#include "GameCore.h"
#include "GameController.h"

void Game_Register()
{
	Engine::Instance().SetGameInitCallback([]() {

		GameController::Instance().Init();

		});
}