#include "Login.h"

Login::Login(const EParams* const params, QQuickWindow* window) :
	IWindow(params, window),
	m_state(EState::Unknown)
{
	m_pRegistrationScreen = new RegistrationScreen(params);
}

Login::~Login()
{
	SAFE_DELETE(m_pRegistrationScreen);
}

void Login::Initialize()
{
	m_pRegistrationScreen->Initialize();

	RegistrationSection* section = qobject_cast<RegistrationSection*>(m_pRegistrationScreen->Section(RegistrationScreen::ETypeSection::RegistrationField));
	connect(section, &RegistrationSection::onSuccess, this, [=]() {
		emit onClosing();
		});
	connect(section, &RegistrationSection::onDuplicateUsername, this, [=]() {
		emit duplicateUsername();
		});
	connect(section, &RegistrationSection::onUserIsNotFound, this, [=]() {
		emit userIsNotFound();
		});

	ToLogin("1", "1"); // TEMP
}

void Login::ToLogin(QString username, QString password)
{
	Query query;
	query.InsertIntoHeader("username", username);
	query.InsertIntoHeader("password", password);
	query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Check_This_User));

	ISection* section = m_pRegistrationScreen->Section(RegistrationScreen::ETypeSection::RegistrationField);
	emit section->onSendToSocket(section, query.toByteArray());
}

void Login::ToRegistration(QString username, QString password)
{
	Query query;
	query.InsertIntoHeader("username", username);
	query.InsertIntoHeader("password", password);
	query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Create_New_User));

	ISection* section = m_pRegistrationScreen->Section(RegistrationScreen::ETypeSection::RegistrationField);
	emit section->onSendToSocket(section, query.toByteArray());
}

Q_INVOKABLE void Login::getLoginAndPassword(QString user, QString pass, int state)
{
	EState st = static_cast<EState>(state);

	if (st == EState::Login)
	{
		ToLogin(user, pass);
	}
	else if (st == EState::Registration)
	{
		ToRegistration(user, pass);
	}	
}
