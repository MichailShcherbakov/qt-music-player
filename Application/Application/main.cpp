#include "Core/Core.h"

int main(int argc, char *argv[])
{
	//QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
	//QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software);

	QGuiApplication app(argc, argv);

	MSG(ETypeMessage::Log, "Core start");
	
	Core core;
	core.Run();

	return app.exec();
}
