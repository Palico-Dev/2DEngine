#include "GameCore.h"
#include "SceneTestComponent1.h"

extern void Game_Register();
extern void MTB_251123();
extern void MTB_251125();
int main(int argc, char** argv)
{
	
	//try
	//{
	//	Game_Register();

	//	Engine::Instance().Initialize();
	//	Engine::Instance().GameLoop();
	//	Engine::Instance().Destroy();
	//}
	//catch (std::exception& e)
	//{
	//	std::cout << "Error occured: " << e.what() << std::endl;
	//}
	 
	// 1. Comment try block above and 
	// 2. Uncomment to run the MTB_251123 test
	MTB_251123();
	//MTB_251125();
	 return 0;
} 
