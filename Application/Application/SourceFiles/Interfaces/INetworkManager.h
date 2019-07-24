#ifndef _INETWORK_MANAGER_H_
#define _INETWORK_MANAGER_H_

#include <QObject>
#include "Query.h"
#include "INetwork.h"

class INetworkManager : public INetwork
{
	Q_OBJECT

public:
	INetworkManager(Socket* socket) 
		: INetwork()
	{
		connect(this, &INetwork::sendToSocket, socket, &Socket::SendToServer);
	}
	~INetworkManager() {}
};

#endif





