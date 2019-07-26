#include "StdAfx.h"
#include "Login.h"

Login::Login(QQuickWindow* window) :
	IWindow(window)
{
	gParams->pRootContext->setContextProperty("wlRoot", this);

	m_pRegistrationScreen = new RegistrationScreen();
}

Login::~Login()
{
	SAFE_DELETE(m_pRegistrationScreen);
}

void Login::Initialize()
{
	m_pRegistrationScreen->Initialize();

	RegistrationSection* section = qobject_cast<RegistrationSection*>(m_pRegistrationScreen->Section(RegistrationScreen::ETypeSection::RegistrationField));

	connect(section, &RegistrationSection::success, this, [=]() {
		emit closing();
		});

	gParams->pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Login/main.qml")));
	m_pWindow = static_cast<QQuickWindow*>(gParams->pEngine->rootObjects().first());
}