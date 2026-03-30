#pragma once

#ifndef _NETWORKENGINE_H_
#define _NETWORKENGINE_H_

#include "NetworkCommon.h"
#include "BitStream.h"

class NetworkEngine final
{
	DECLARE_SINGLETON(NetworkEngine)
	friend class Engine;

public:
	enum NetworkState
	{
		NONE,
		INITIALIZE_NETWORK,
		WAITING_FOR_CONNECTIONS,
		RUNNING,
		DISABLE,
		NETWORK_ERROR,
	};

public:
	inline bool IsClient() const { return isClient; }
	inline bool IsServer() const { return isServer; }
	inline NetworkState GetState() const { return state; }

	void SendPacket(RakNet::BitStream& bs, RakNet::RakNetGUID* guid = nullptr);

	void RegisterPacketCallback(int packetId,
		std::function<void(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)>* callback);

	void UnRegisterPacketCallback(int packetId,
		const std::function<void(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)>* callback);


private:
	void Initialize(bool _isServer);
	void InitializeNetwork();
	void LoadSetting();
	void PreUpdate();
	void ReceivePackets();
		 

private:
	bool isServer = false;
	bool isClient = false;
	NetworkState state = NetworkState::NONE;

	int port = -1;
	std::string ipAddress;
	RakNet::RakPeerInterface* rakInterface = nullptr;
	std::vector<RakNet::RakNetGUID> connections;

	std::map<int, std::vector<std::function<void(RakNet::BitStream& _bitStream, RakNet::RakNetGUID& guid)>*>> NetworkPacketCallbacks;
};

#endif


