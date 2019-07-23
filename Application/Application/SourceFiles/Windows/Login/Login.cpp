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

	ToLogin("1", "1");
}

void Login::ToLogin(QString username, QString password)
{
	QCryptographicHash hash(QCryptographicHash::Keccak_512);
	int length = hash.hashLength(QCryptographicHash::Keccak_512);

	hash.addData(QString(username + password).toLatin1());

	Query query;
	query.InsertIntoHeader("hashCode", QString::fromLatin1(hash.result(), length));
	query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Check_This_User));

	ISection* section = qobject_cast<ISection*>(m_pRegistrationScreen->Section(RegistrationScreen::ETypeSection::RegistrationField));
	emit section->onSendToSocket(section, query.toByteArray());
}

void Login::ToRegistration(QString username, QString password)
{
	QCryptographicHash hash(QCryptographicHash::Keccak_512);
	int length = hash.hashLength(QCryptographicHash::Keccak_512);

	hash.addData(QString(username + password).toLatin1());

	Query query;
	query.InsertIntoHeader("hashCode", QString::fromLatin1(hash.result(), length));
	query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Create_New_User));

	ISection* section = qobject_cast<ISection*>(m_pRegistrationScreen->Section(RegistrationScreen::ETypeSection::RegistrationField));
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
