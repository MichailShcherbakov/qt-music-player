#ifndef _CQUERY_H_
#define _CQUERY_H_

#include "StdAfx.h"

#include <QString>
#include <QByteArray>

class CQuery
{
public:
	CQuery();
	CQuery(QString user, QString password);
	~CQuery();

public:
	void NewQuery(EQuery type);
	void NewQuery(EQuery type, ETable type2);
	void NewQuery(QByteArray* array);
	void NewQuery(EQuery type, QString param, QString param2);
	void SetUserName(QString name);
	void SetUserPassword(QString name);
	QByteArray* toByteArray();

private:
	QString m_user;
	QString m_password;
	QByteArray* buffer = nullptr;
};

#endif // !_CQUERY_H_





