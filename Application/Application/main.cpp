#include <QGuiApplication>
#include <QQuickWindow>

#include "CMain.h"


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>


#include <QTextCodec>

enum class ETypeQuery : int 
{
	Unknown = -1,
	Create_New_User,
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

	QJsonDocument docHeader, docBody, docFooter;
	QJsonObject header, body, footer;

	/* body */
	body.insert("media-data", QJsonValue(QString::fromLatin1(fArr.data(), fArr.size())));
	docBody.setObject(body);

	/* header*/
	header.insert("type-query", QJsonValue(static_cast<int>(ETypeQuery::Create_New_User)));
	header.insert("size-body", QJsonValue(docBody.toJson().size()));
	header.insert("username", QJsonValue("user"));
	header.insert("password", QJsonValue("pass"));
	docHeader.setObject(header);

	/* footer */
	docFooter.setObject(footer);

	/* send header */
	socket->sendToServer(&docHeader.toJson());

	/* send body */
	socket->sendToServer(&docBody.toJson());

	/* send footer */
	socket->sendToServer(&docFooter.toJson());

	return app.exec();
}
