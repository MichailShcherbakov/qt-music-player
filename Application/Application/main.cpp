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

	CMain main;
	main.Initialize();

	return app.exec();
}
