#ifndef _REGISTRATION_FIELD_H_
#define _REGISTRATION_FIELD_H_

#include <QCryptographicHash>

#include "Interfaces/ISectionObject.h"

namespace Enums
{
	Q_NAMESPACE

	enum class ETypeEnter : uint
	{
		Unknown = 0,
		Login,
		Registration,
	};

	Q_ENUM_NS(ETypeEnter)
}

class RegistrationSection : public ISectionObject
{
	Q_OBJECT
	Q_PROPERTY(Enums::ETypeEnter type MEMBER m_type NOTIFY typeChanged)
	Q_PROPERTY(QString username MEMBER m_username NOTIFY usernameChanged)
	Q_PROPERTY(QString password MEMBER m_password NOTIFY passwordChanged)
	Q_PROPERTY(bool remember MEMBER m_remember NOTIFY rememberChanged)

public:
	RegistrationSection();
	~RegistrationSection() override;

public slots:
	// ISection
	virtual void Initialize() override;
	virtual void ReadyRead(QByteArray package) override;
	virtual void GottenData(QByteArray data) override;
	// ~ISection

signals:
	void entered();
	void typeChanged();
	void usernameChanged();
	void passwordChanged();
	void rememberChanged();
	void success();
	void duplicateUsername();
	void userIsNotFound();

private:
	Enums::ETypeEnter m_type = Enums::ETypeEnter::Unknown;
	QString m_username;
	QString m_password;
	bool m_remember = false;
};


#endif
