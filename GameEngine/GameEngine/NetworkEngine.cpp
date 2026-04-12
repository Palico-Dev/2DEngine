#include "EngineCore.h"
#include "NetworkEngine.h"
#include "Engine.h"
#include "FileManager.h"

void NetworkEngine::SendPacket(RakNet::BitStream& bs, RakNet::RakNetGUID* guid /*= nullptr*/)
{
	if (guid != nullptr)
	{
		auto itr = std::find(connections.begin(), connections.end(), *guid);
		if (itr != connections.end())
		{
			rakInterface->Send(&bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, *guid, false);
		}
	}
	else
	{
		for (int i = 0; i < connections.size(); i++)
		{
			rakInterface->Send(&bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, connections[i], false);
		}
	}
}

void NetworkEngine::SendMessage(const std::string& message, RakNet::RakNetGUID* guid /*= nullptr*/)
{
	RakNet::BitStream bs;
	bs.Write((unsigned char)NetworkPacketIds::ID_MSG);

	RakNet::RakString rakString(message.c_str());
	bs.Write(rakString);

	SendPacket(bs, guid);
}

void NetworkEngine::RegisterPacketCallback(int packetId, std::function<void(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)>* callback)
{
	NetworkPacketCallbacks[packetId].push_back(callback);
}

void NetworkEngine::UnRegisterPacketCallback(int packetId, const std::function<void(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)>* callback)
{
	auto itr = NetworkPacketCallbacks.find(packetId);
	if (itr != NetworkPacketCallbacks.end())
	{
		NetworkPacketCallbacks[packetId].erase(
			std::remove(
				NetworkPacketCallbacks[packetId].begin(),
				NetworkPacketCallbacks[packetId].end(), callback
			),
			NetworkPacketCallbacks[packetId].end()
		);
	}
}

void NetworkEngine::KickAllClients()
{
	if(Engine::Instance().GetRole() != EngineRole::Server)
		return;

	for (auto& guid : connections)
	{
		rakInterface->CloseConnection(guid, true);
	}
}

void NetworkEngine::Initialize()
{
	if (Engine::Instance().GetRole() == EngineRole::Standalone)
	{
		state = NetworkState::DISABLE;
		return;
	}
	LoadSetting();

	rakInterface = RakNet::RakPeerInterface::GetInstance();
	state = NetworkState::INITIALIZE_NETWORK;
}

void NetworkEngine::InitializeNetwork()
{
	EngineRole role = Engine::Instance().GetRole();

	if (role == EngineRole::Standalone)
	{
		state = NetworkState::DISABLE;
		return;
	}

	if (role == EngineRole::Client)
	{
		RakNet::SocketDescriptor sd(0, NULL);

		if (rakInterface->Startup(1, &sd, 1) != RakNet::RAKNET_STARTED)
		{
			Debug::Error("*** Failed to start client on port " + port);
			exit(1);
		}

		if (rakInterface->Connect(ipAddress.c_str(), port, NULL, 0) != RakNet::CONNECTION_ATTEMPT_STARTED)
		{
			Debug::Warning("*** Failed to connect to server. Going to try later " + port);
		}
	}
	else if (role == EngineRole::Server)
	{
		RakNet::SocketDescriptor sd(port, NULL);
		if (rakInterface->Startup(8, &sd, 1) != RakNet::RAKNET_STARTED)
		{
			Debug::Error("*** Failed to start server on port " + port);
			exit(1);
		}

		// set maximum number of incoming connections
		rakInterface->SetMaximumIncomingConnections(8);
	}
	state = NetworkEngine::RUNNING;
}

void NetworkEngine::LoadSetting()
{
	//std::ifstream inputStream("../Assets/NetworkSettings.json");
	//std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON gamesetting = Engine::Instance().GetGameSettings();
	json::JSON document = FileManager::JsonReadJson(gamesetting, "NetworkSetting");

	THROW_RUNTIME_ERROR(document.hasKey("ipaddress") == false, "Unable to determine ip address");
	ipAddress = document["ipaddress"].ToString();

	THROW_RUNTIME_ERROR(document.hasKey("port") == false, "Unable to determine ip address");
	port = document["port"].ToInt();
}

void NetworkEngine::PreUpdate()
{
	if (Engine::Instance().GetRole() == EngineRole::Standalone)
		return;

	switch (state)
	{
	case NetworkEngine::INITIALIZE_NETWORK:
		if (rakInterface->IsActive())
		{
			rakInterface->Shutdown(0);
		}
		InitializeNetwork();
		break;
	case NetworkEngine::RUNNING:
		ReceivePackets();
		break;
	case NetworkEngine::DISABLE:
		break;
	default:
		break;
	}
}

void NetworkEngine::ReceivePackets()
{
	unsigned char packetId;

	// get a packet
	RakNet::Packet* packet = rakInterface->Receive();

	while (packet != NULL)
	{
		RakNet::BitStream bs(packet->data, packet->length, false);

		bs.Read(packetId);

		switch (packetId)
		{

		case ID_CONNECTION_REQUEST_ACCEPTED:
			if (Engine::Instance().GetRole() == EngineRole::Client)
			{
				std::cout << "Connected to " << packet->systemAddress.ToString(true) << std::endl;
				connections.push_back(packet->guid);
				state = NetworkState::RUNNING;
			}
			break;
		case ID_NEW_INCOMING_CONNECTION:
			// Somebody connected
			std::cout << "Got connection from " << packet->systemAddress.ToString(true) << std::endl;
			connections.push_back(packet->guid);
			break;

		case ID_CONNECTION_LOST:
		case ID_DISCONNECTION_NOTIFICATION:
			connections.erase(std::find(connections.begin(), connections.end(), packet->guid));
			std::cout << "Connection lost to " << packet->systemAddress.ToString(true) << std::endl;
			state = NetworkState::WAITING_FOR_CONNECTIONS;
			break;

		case ID_CONNECTION_ATTEMPT_FAILED:
			state = NetworkState::NETWORK_ERROR;
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			state = NetworkState::NETWORK_ERROR;
			break;
		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
			state = NetworkState::NETWORK_ERROR;
			break;
		}

		auto itr = NetworkPacketCallbacks.find(packetId);
		if (itr != NetworkPacketCallbacks.end())
		{
			for (auto& callback : itr->second)
			{
				(*callback)(bs, packet->guid);
			}
		}

		rakInterface->DeallocatePacket(packet);

		// get next packet
		packet = rakInterface->Receive();
	}
}
