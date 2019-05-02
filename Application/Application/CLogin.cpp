#include "CLogin.h"

CLogin::CLogin(QQuickWindow* window, CQuery* query) :
	IWindow(window, query),
	m_state(EState::Unknown)
{
}

CLogin::~CLogin()
{
}

void CLogin::Initialize()
{
}

void CLogin::getFromSocket(QByteArray* data)
{
	int check = static_cast<int>(ELoginAndRegistration::Unknown);
	QDataStream in(data, QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_5_12);
	in >> check;

	SAFE_DELETE(data);

	switch (m_state)
	{
	case EState::Registration:
	{
		switch (static_cast<ELoginAndRegistration>(check))
		{
		case ELoginAndRegistration::Duplicated:
		{
			break;
		}
		case ELoginAndRegistration::Error:
		{
			break;
		}
		case ELoginAndRegistration::Success:
		{
			emit closing();
			break;
		}
		}
		break;
	}
	case EState::Login:
	{
		switch (static_cast<ELoginAndRegistration>(check))
		{
		case ELoginAndRegistration::Duplicated:
		{
			break;
		}
		case ELoginAndRegistration::Error:
		{
			break;
		}
		case ELoginAndRegistration::Success:
		{
			emit closing();
			break;
		}
		}
		break;
	}
	}
}

void CLogin::ToLogin(QString name, QString password)
{
	m_query->SetUserName(name);
	m_query->SetUserPassword(password);
	m_query->NewQuery(m_query->CHECK_USER);
	m_state = EState::Login;
	emit sendToSocket(m_query->toByteArray());
}

void CLogin::ToRegistration(QString name, QString password)
{
	m_query->SetUserName(name);
	m_query->SetUserPassword(password);
	m_query->NewQuery(m_query->CREATE_NEW_USER);
	m_state = EState::Registration;
	emit sendToSocket(m_query->toByteArray());
}

Q_INVOKABLE void CLogin::getLoginAndPassword(QString user, QString pass, int state)
{
	EState st = static_cast<EState>(state);

	if (st == EState::Login)
		ToLogin(user, pass);
	else if (st == EState::Registration)
		ToRegistration(user, pass);
}
