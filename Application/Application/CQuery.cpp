#include "CQuery.h"

CQuery::CQuery()
{
}

CQuery::CQuery(QString user, QString password)
{
	m_user = user;
	m_password = password;
}

CQuery::~CQuery()
{
	SAFE_DELETE(buffer);
}

void CQuery::NewQuery(EQuery type)
{
	if (buffer == nullptr)
		buffer = new QByteArray;
	else
		buffer->clear();

	QString qery = "[" + m_user + "]"
		+ "[" + m_password + "]"
		+ "[" + QString::number(static_cast<int>(type)) + "]";

	buffer->append(qery.toUtf8());
}

void CQuery::NewQuery(EQuery type, ETable type2)
{
	if (buffer == nullptr)
		buffer = new QByteArray;
	else
		buffer->clear();

	QString qery = "[" + m_user + "]"
		+ "[" + m_password + "]"
		+ "[" + QString::number(static_cast<int>(type)) + "]"
		+ "[" + QString::number(static_cast<int>(type2)) + "]";

	buffer->append(qery.toUtf8());
}

void CQuery::NewQuery(QByteArray* array)
{
	if (buffer == nullptr)
		buffer = new QByteArray;
	else
		buffer->clear();

	buffer->append(*array);
}

void CQuery::NewQuery(EQuery type, QString param, QString param2)
{
	if (buffer == nullptr)
		buffer = new QByteArray;
	else
		buffer->clear();

	QString qery = "[" + m_user + "]"
		+ "[" + m_password + "]"
		+ "[" + QString::number(static_cast<int>(type)) + "]"
		+ "[" + param + "]"
		+ "[" + param2 + "]";

	buffer->append(qery.toUtf8());
}

void CQuery::SetUserName(QString name)
{
	m_user = name;
}

void CQuery::SetUserPassword(QString pass)
{
	m_password = pass;
}

QByteArray* CQuery::toByteArray()
{
	return buffer;
}