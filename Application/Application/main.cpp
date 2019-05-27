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

	m_socket->sendToServer(&QString("[123][123][1]").toUtf8());

	return app.exec();
}
