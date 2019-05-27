#ifndef _CQUERY_H_
#define _CQUERY_H_

#include <QByteArray>
#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlDatabase>

#include "ServerTools.h"

using namespace STools;

enum EQuery : int
{
	SEND_MEDIA,
	CREATE_NEW_USER,
	CHECK_USER,
	SEND_TABLE,
	ADD_NEW_MEDIA,
	SEND_IMAGE,
};

enum class ETable : ushort
{
	Unknown = -1,
	All_Music,
};

class CQuery
{
public:
	CQuery();
	CQuery(QByteArray arr);
	~CQuery();

public:
	void		ConvertMsg(QByteArray arr);
	int			GetID();
	QString		GetUser();
	QString		GetPassword();
	QString		GetType();
	QString		GetValue_1();
	QString		GetValue_2();
	bool		Check();

private:
	QString user, password, type, value_1, value_2;
};

#endif
