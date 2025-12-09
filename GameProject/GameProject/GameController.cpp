#include "GameCore.h"
#include "GameController.h"
#include "DataBindingRegistry.h"

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
}

void GameController::LoseHealth()
{

}

void GameController::RestartGame()
{

}

void GameController::AddScore(int add)
{
	score += add;
	if (score > highestScore)
		highestScore = score;
}
