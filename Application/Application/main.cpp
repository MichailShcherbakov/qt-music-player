#include <QGuiApplication>
#include <QQuickWindow>

#include "CMain.h"


int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQuickWindow::setSceneGraphBackend(QSGRendererInterface::OpenGL);

	app.setOrganizationName("Some Company");
	app.setOrganizationDomain("somecompany.com");
	app.setApplicationName("Amazing Application");

	// Network
	CSocket* m_socket = new CSocket;
	m_socket->Initialize();

	QFile f("C:/Users/User/Desktop/03 - Enough.mp3");
	f.open(QIODevice::ReadOnly);
	QByteArray arr = f.readAll();
	f.close();

	QByteArray message;

	QDataStream out(&message, QIODevice::WriteOnly);
	out << arr;

	m_socket->sendToServer(&QString("[123][123][4][true][true]").toUtf8());
	m_socket->sendToServer(&message);

	return app.exec();
}
