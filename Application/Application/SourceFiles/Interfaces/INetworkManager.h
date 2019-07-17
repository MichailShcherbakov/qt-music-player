#ifndef _INETWORK_MANAGER_H_
#define _INETWORK_MANAGER_H_

#include "StdAfx.h"

#include <QObject>
#include "Query.h"
#include "INetwork.h"
#include "Network/Socket/Socket.h"

class INetworkManager : public INetwork
{
	Q_OBJECT

public:
	INetworkManager(Socket* socket) 
		: INetwork()
	{
		connect(this, &INetwork::onSendToSocket, socket, &Socket::SendToServer);
	}
	~INetworkManager() {}
};

#endif // !_CSOCKET_H_





