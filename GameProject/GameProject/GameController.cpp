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

	registry.RegisterString(GetHashCode("PLAYER_SCORE"), [this]() {
		return "Score: " + std::to_string(this->score);
		});

	registry.RegisterString(GetHashCode("PLAYER_HIGHESTSCORE"), [this]() {
		return "Highest Score: " + std::to_string(this->highestScore);
		});

	registry.RegisterString(GetHashCode("FPS"), []() {
		return std::to_string(Time::Instance().FPS());
		});

	registry.RegisterInt(GetHashCode("GAME_HEALTH"), [this]() {
		return this->gameHealth;
		});
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
