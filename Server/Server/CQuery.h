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
	UNKNOWN = -1,
	SEND_MEDIA,
	CREATE_NEW_USER,
	CHECK_USER,
	SEND_TABLE,
	ADD_NEW_MEDIA,
	ADD_NEW_MEDIA_RETURN,
	SEND_IMAGE,
};

enum ETable : int
{
	ALL_MEDIA,
	ALL_ALBUMS,
	ALL_ARTISTS,
	ALL_GENRES
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
