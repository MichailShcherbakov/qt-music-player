#include "CQuery.h"



CQuery::CQuery()
{
}

CQuery::CQuery(QByteArray arr)
{
	ConvertMsg(arr);
}

CQuery::~CQuery()
{
}

void CQuery::ConvertMsg(QByteArray arr)
{
	QString msg = QString::fromUtf8(arr);

	for (int i = 0, k = 0; i < msg.size(); ++i, ++k)
	{
		++i;
		while (msg[i] != ']')
		{
			switch (k)
			{
			case 0:
			{
				user += msg[i];
				break;
			}
			case 1:
			{
				password += msg[i];
				break;
			}
			case 2:
			{
				type += msg[i];
				break;
			}
			case 3:
			{
				value_1 += msg[i];
				break;
			}
			case 4:
			{
				value_2 += msg[i];
				break;
			}
			}
			++i;
		}
	}
}

QString CQuery::GetUser()
{ 
	return user; 
}

QString CQuery::GetPassword() 
{ 
	return password; 
}

QString CQuery::GetType()
{ 
	return type; 
}

QString CQuery::GetValue_1()
{ 
	return value_1; 
}

QString CQuery::GetValue_2()
{ 
	return value_2; 
}

int CQuery::GetID()
{
	QSqlQuery q;
	q.exec("USE data_server;");
	q.exec("SELECT * FROM users;");
	while (q.next())
	{
		if (q.value(1).toString() == user && q.value(2).toString() == password)
		{
			return q.value(0).toInt();
		}
	}
	return -1;
}

bool CQuery::Check()
{
	QSqlQuery q;
	q.exec("USE data_server;");
	q.exec("SELECT * FROM users;");
	while (q.next())
	{
		if (q.value(1).toString() == user && q.value(2).toString() == password)
		{
			Msg(EMessage::Success, "The user is confirmed");
			return true;
		}
	}
	Msg(EMessage::Error, "The user isn't confirmed");
	return false;
}