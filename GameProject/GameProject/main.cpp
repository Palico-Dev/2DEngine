#include "GameCore.h"
#include "FileManager.h"

extern void Game_Register();
int main(int argc, char** argv)
{

	Game_Register();
	Debug::Log(FileManager::GetAssetPath().string());
	Debug::Log(FileManager::GetEngineAssetPath().string());
	Engine::Instance().Initialize();
	//Engine::Instance().GameLoop();
	//Engine::Instance().Destroy();
	return 0;
}
