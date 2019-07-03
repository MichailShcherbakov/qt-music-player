#include "Core/Core.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Direct3D12);

	QGuiApplication app(argc, argv);

	Core core;
	core.Run();

	return app.exec();
}
