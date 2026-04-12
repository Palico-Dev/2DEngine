#include "GameCore.h"
#include "GameController.h"
#include "DataBindingRegistry.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Transform.h"
#include "FileManager.h"

void GameController::Init()
{
	auto& registry = DataBindingRegistry::Instance();
}

void GameController::LoseHealth()
{
	SceneManager::Instance().GetCurrentScene()->CleanScene();
	player->transform->SetPosition({ 375,700 });
	gameHealth--;

	if (gameHealth <= 0)
		RestartGame();
}

void GameController::Start()
{
	player = Gameplay::FindAllEntitiesWithTag("Player")[0];
}

void GameController::RestartGame()
{
	score = 0;
	gameHealth = 3;
}

void GameController::AddScore(int add)
{
	score += add;
	if (score > highestScore)
		highestScore = score;
}

void GameController::Serialize(json::JSON& j)
{
	json::JSON node;
	FileManager::JsonWriteInt(node, "highestScore", highestScore);
	FileManager::JsonWriteInt(node, "score", score);
	FileManager::JsonWriteInt(node, "gameHealth", gameHealth);
	FileManager::JsonWriteVec2(node, "playerPosition", player->transform->GetPosition());

	j["gameController"] = node;
}

void GameController::Deserialize(json::JSON& j)
{
	json::JSON node = j["gameController"];
	highestScore = FileManager::JsonReadInt(node, "highestScore");
	score = FileManager::JsonReadInt(node, "score");
	gameHealth = FileManager::JsonReadInt(node, "gameHealth");
	player->transform->SetPosition(FileManager::JsonReadVec2(node, "playerPosition"));
}

void GameController::ButtonTest()
{
	Debug::Log("ButtonTest");
}

void GameController::PauseGame()
{
	Engine::Instance().ToggleGamePause();
}

void GameController::ResumeGame()
{

}
