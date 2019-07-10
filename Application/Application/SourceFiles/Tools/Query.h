#ifndef _QUERY_H_
#define _QUERY_H_

#include "Tools/StdAfx.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

enum class ETypeQuery : int
{
	Unknown = 0,
	Create_New_User,
	Check_This_User,
	Add_New_Media,
	Send_Table,
	Send_Cover_Art,
	Send_Media,
};

enum class ETypeTable : int
{
	Unknown = 0,
	All_Media,
	All_Genres,
	All_Albums,
	All_Artists,
};

enum class ETypeResultQuery : int 
{
	Unknown = 0,
	Success,
	DuplicateUsername,
	IsNotFound,
	FileIsEmpty,
	UserIsNotFound,
	ReadError,
	InsertError,
	WriteError,
	UserIsNotAuthorized,
};

struct Query
{
public:
	Query() {}
	~Query() {}

public:
	inline void InsertIntoHeader(const QString& title, const QJsonValue& value)
	{
		header.insert(title, value);
	}

	inline void InsertIntoBody(const QString& title, const QJsonValue& value)
	{
		body.insert(title, value);
	}

	inline void InsertIntoFooter(const QString& title, const QJsonValue& value)
	{
		footer.insert(title, value);
	}

	inline QJsonValue GetFromHeader(const QString& title)
	{
		if (header.contains(title))
		{
			return header.value(title);
		}
		return QJsonValue();
	}

	inline QJsonValue GetFromBody(const QString& title)
	{
		if (body.contains(title))
		{
			return body[title];
		}
		return QJsonValue();
	}

	inline QJsonValue GetFromFooter(const QString& title)
	{
		if (footer.contains(title))
		{
			return footer[title];
		}
		return QJsonValue();
	}

	friend bool operator==(const Query& l, const Query& r)
	{
		if (l.doc == r.doc &&
			l.main == r.main &&
			l.header == r.header &&
			l.body == r.body &&
			l.footer == r.footer)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline QByteArray toByteArray()
	{
		main.insert("header", header);
		main.insert("body", body);
		main.insert("footer", footer);
		doc.setObject(main);
		return doc.toJson();
	}

	inline void fromByteArray(QByteArray data)
	{
		doc = QJsonDocument::fromJson(data);
		header = doc["header"].toObject();
		body = doc["body"].toObject();
		footer = doc["footer"].toObject();
	}

private:
	QJsonDocument doc;
	QJsonObject main;
	QJsonObject header;
	QJsonObject body;
	QJsonObject footer;
};

#endif
