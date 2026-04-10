#include "GameCore.h"
#include "FileManager.h"

//#define DEV_ROLE_SERVER
//#define DEV_ROLE_CLIENT
//#define DEV_ROLE_STANDALONE

extern void Game_Register();
int main(int argc, char* argv[])
{
	EngineRole currentRole = EngineRole::Standalone;

#ifdef DEV_ROLE_SERVER
	currentRole = EngineRole::Server;
#elif defined(DEV_ROLE_CLIENT)
	currentRole = EngineRole::Client;
#elif defined(DEV_ROLE_STANDALONE)
	currentRole = EngineRole::Standalone;
#endif

	for (int i = 1;i < argc;++i)
	{
		std::string_view arg(argv[i]);

		if (arg == "--server" || arg == "-s")
		{
			currentRole = EngineRole::Server;
		}
		else if (arg == "--client" || arg == "-c")
		{
			currentRole = EngineRole::Client;
		}
		else if (arg == "--standalone")
		{
			currentRole = EngineRole::Standalone;
		}
	}

	Game_Register();


	Engine::Instance().Initialize(currentRole);


	Engine::Instance().GameLoop();
	Engine::Instance().Destroy();
	return 0;
}
