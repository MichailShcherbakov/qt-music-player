#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "Interfaces/IWindow.h"

#include "Screens/Registration/RegistrationScreen.h"

class Login : public IWindow
{
	Q_OBJECT

public:
	Login(QQuickWindow* window = Q_NULLPTR);
	~Login() override;

public:
	// IWindow
	virtual void Initialize() override;
	// ~IWindowe

private:
	RegistrationScreen* m_pRegistrationScreen;
};

#endif
