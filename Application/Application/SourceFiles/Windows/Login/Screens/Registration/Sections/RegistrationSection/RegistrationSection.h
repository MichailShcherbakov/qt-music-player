#ifndef _REGISTRATION_FIELD_H_
#define _REGISTRATION_FIELD_H_

#include "StdAfx.h"

#include "Interfaces/ISection.h"

class RegistrationSection : public ISection
{
	Q_OBJECT

public:
	RegistrationSection(const EParams* const params);
	~RegistrationSection() override;

public slots:
	// ISection
	virtual void Initialize() override;
	virtual void ReadyRead(QByteArray package) override;
	virtual void GottenData(QByteArray data) override;
	// ~ISection

signals:
	void onSuccess();
	void onDuplicateUsername();
	void onUserIsNotFound();
};


#endif
