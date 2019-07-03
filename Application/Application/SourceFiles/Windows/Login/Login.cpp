#include "Login.h"

Login::Login(QQuickWindow* window) :
	IWindow(window),
	m_state(EState::Unknown)
{
}

Login::~Login()
{
}

void Login::Initialize()
{
}

void Login::GetFromSocket(QByteArray data)
{
	Query result;
	result.fromByteArray(data);

	ETypeResultQuery res = static_cast<ETypeResultQuery>(result.GetFromHeader("query-result").toInt());

	switch (res)
	{
	case ETypeResultQuery::Success:
	{
		emit onClosing();
		break;
	}
	case ETypeResultQuery::DuplicateUsername:
	{
		duplicateUsername();
		break;
	}
	case ETypeResultQuery::UserIsNotFound:
	{
		userIsNotFound();
		break;
	}
	}
}

void Login::ToLogin(QString username, QString password)
{
	Query query;
	query.InsertIntoHeader("username", username);
	query.InsertIntoHeader("password", password);
	query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Check_This_User));
	emit onSendToSocket(query.toByteArray());
}

void Login::ToRegistration(QString username, QString password)
{
	Query query;
	query.InsertIntoHeader("username", username);
	query.InsertIntoHeader("password", password);
	query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Create_New_User));
	emit onSendToSocket(query.toByteArray());
}

Q_INVOKABLE void Login::getLoginAndPassword(QString user, QString pass, int state)
{
	EState st = static_cast<EState>(state);

	if (st == EState::Login)
		ToLogin(user, pass);
	else if (st == EState::Registration)
		ToRegistration(user, pass);
}
