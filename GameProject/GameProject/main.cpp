#include "GameCore.h"

extern void Game_Register();
int main(int argc, char** argv)
{

	Game_Register();

	Engine::Instance().Initialize();
	Engine::Instance().GameLoop();
	Engine::Instance().Destroy();
	return 0;
}
