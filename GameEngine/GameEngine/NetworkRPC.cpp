#include "EngineCore.h"
#include "NetworkRPC.h"

void NetworkRPC::InvokeRPC(RakNet::BitStream& bitStream)
{
	STRCODE functionID;
	bitStream.Read(functionID);

	auto itr = rpcFunctions.find(functionID);
	if(itr != rpcFunctions.end())
	{
		itr->second(bitStream);
	}
}

void NetworkRPC::RegisterRPC(STRCODE functionName, std::function<void(RakNet::BitStream&)> functionPtr)
{
	rpcFunctions.emplace(functionName, functionPtr);
}
