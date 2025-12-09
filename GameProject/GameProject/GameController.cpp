#include "GameCore.h"
#include "GameController.h"
#include "DataBindingRegistry.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Transform.h"

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
	//SceneManager::Instance().GetCurrentScene()->CleanScene();
	//player->transform->SetPosition({ 375,700 });
	//gameHealth--;

	//if (gameHealth <= 0)
	//	RestartGame();
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
