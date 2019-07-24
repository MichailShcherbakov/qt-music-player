#ifndef _INETWORK_H_
#define _INETWORK_H_

#include <QObject>

class INetwork : public QObject
{
	Q_OBJECT

public:
	INetwork()
		: m_pBuffer(Q_NULLPTR)
	{
		connect(this, &INetwork::getFromSocket, this, [=](QByteArray data) { m_pBuffer.append(data); });
	}
	~INetwork() {}

public slots:
	inline void GetFromSocket(const QByteArray data) { emit getFromSocket(data); }
	inline void GetSizeData(const unsigned int size) { emit getSizeData(size); }

signals:
	void getFromSocket(const QByteArray data);
	void getSizeData(const unsigned int size);
	void sendToSocket(INetwork* sender, const QByteArray query);
	void loaded();

protected:
	QByteArray m_pBuffer;
};

#endif // !_CSOCKET_H_





