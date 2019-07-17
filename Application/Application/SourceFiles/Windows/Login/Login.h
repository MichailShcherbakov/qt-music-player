#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "StdAfx.h"
#include "EParams.h"

#include "Interfaces/IWindow.h"
#include "Screens/Registration/RegistrationScreen.h"

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
	Login(const EParams* const params, QQuickWindow* window = Q_NULLPTR);
	~Login() override;

public:
	// IWindow
	virtual void Initialize() override;
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
	RegistrationScreen* m_pRegistrationScreen;
	EState m_state;
};

#endif
