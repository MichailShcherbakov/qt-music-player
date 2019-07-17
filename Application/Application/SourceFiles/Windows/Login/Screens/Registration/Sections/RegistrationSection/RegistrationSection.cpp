#include "RegistrationSection.h"

RegistrationSection::RegistrationSection(const EParams* const params)
	: ISection(params)
{
}

RegistrationSection::~RegistrationSection()
{
}

void RegistrationSection::Initialize()
{
}

void RegistrationSection::ReadyRead(QByteArray package)
{
}

void RegistrationSection::GottenData(QByteArray data)
{
	Query result;
	result.fromByteArray(data);

	ETypeResultQuery res = static_cast<ETypeResultQuery>(result.GetFromHeader("query-result").toInt());

	switch (res)
	{
	case ETypeResultQuery::Success:
	{
		emit onSuccess();
		break;
	}
	case ETypeResultQuery::DuplicateUsername:
	{
		emit onDuplicateUsername();
		break;
	}
	case ETypeResultQuery::UserIsNotFound:
	{
		emit onUserIsNotFound();
		break;
	}
	}
}
