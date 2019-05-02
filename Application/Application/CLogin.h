#ifndef _C_LOGIN_H_
#define _C_LOGIN_H_

#include "StdAfx.h"
#include "IWindow.h"

class CLogin : public IWindow
{
	Q_OBJECT

public:
	CLogin(QQuickWindow* window, CQuery* query);
	virtual ~CLogin();

private:
	enum class EState : int
	{
		Unknown = -1,
		Login,
		Registration,
	};

	enum class ELoginAndRegistration : int
	{
		Unknown = -1,
		Error,
		Success,
		Duplicated
	};

public:
	// IWindow
	virtual void Initialize() override;
	virtual void getFromSocket(QByteArray* data) override;
	// ~IWindow

private:
	void ToLogin(QString name, QString password);
	void ToRegistration(QString name, QString password);

public:
	Q_INVOKABLE void getLoginAndPassword(QString user, QString pass, int state);

private:
	EState m_state;
};

#endif
