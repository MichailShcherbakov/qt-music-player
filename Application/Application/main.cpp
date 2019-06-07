#include <QGuiApplication>
#include <QQuickWindow>

#include "CMain.h"


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

enum class ETypeQuery : int
{
	Unknown = -1,
	Create_New_User,
	Check_This_User,
	Add_New_Media,
	Send_Table,
	Send_Cover_Art,
	Send_Media,
};

enum class ETypeTable : int
{
	Unknown = -1,
	All_Media,
	All_Genres,
	All_Albums,
	All_Artists,
};

enum class ETypeResult : int {
	Unknown = -1,
	Success,
	Error,
	Duplicate_Username,
};

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQuickWindow::setSceneGraphBackend(QSGRendererInterface::OpenGL);

	app.setOrganizationName("Some Company");
	app.setOrganizationDomain("somecompany.com");
	app.setApplicationName("Amazing Application");

	/*CMain main;
	main.Initialize();*/

	CSocket* socket = new CSocket;
	socket->Initialize();

	QFile f("C:/USers/User/Desktop/03 - Enough.mp3");
	f.open(QIODevice::ReadOnly);
	QByteArray fArr = f.readAll();
	f.close();

	QJsonDocument doc;
	QJsonObject main, header, body, footer;

	/* header */
	header.insert("type-query", QJsonValue(static_cast<int>(ETypeQuery::Create_New_User)));
	header.insert("username", QJsonValue("user"));
	header.insert("password", QJsonValue("pass"));
	main.insert("header", header);

	/* body */
	body.insert("media-data", QJsonValue(QString::fromLatin1(fArr.data(), fArr.size())));
	main.insert("body", body);

	/* footer */
	main.insert("footer", footer);

	doc.setObject(main);

	/* send doc */
	socket->sendToServer(&doc.toJson());

	return app.exec();
}
