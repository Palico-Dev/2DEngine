#include "GameCore.h"
#include "GameController.h"
#include "SaveManager.h"
void Game_Register()
{
	Engine::Instance().SetGameInitCallback([]() {

		GameController::Instance().Init();

		});

	Engine::Instance().SetGameStartCallback([]() {

		GameController::Instance().Start();

		});

	SaveManager::Instance().SetGameSerialize([](json::JSON& j) {

		GameController::Instance().Serialize(j);

		});


}