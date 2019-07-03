#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "Tools/StdAfx.h"

#include "Interfaces/IWindow.h"

enum class EState : int
{
	Unknown = -1,
	Login,
	Registration,
};

class Login : public IWindow
{
	Q_OBJECT

public:
	Login(QQuickWindow* window);
	virtual ~Login();

public:
	// IWindow
	virtual void Initialize() override;
	virtual void GetFromSocket(QByteArray data) override;
	// ~IWindow

private:
	void ToLogin(QString name, QString password);
	void ToRegistration(QString name, QString password);

signals:
	void duplicateUsername();
	void userIsNotFound();

public:
	Q_INVOKABLE void getLoginAndPassword(QString user, QString pass, int state);

private:
	EState m_state;
};

#endif
