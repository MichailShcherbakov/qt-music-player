#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <QDir>
#include <QObject>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlDatabase>
#include <QCoreApplication>

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

#include "Tools/LogSystem.h"

struct Tags
{
	QString Title;
	QString Artist;
	QString Album;
	QString Genre;
	QString Year;
	QString Bitrate;
	QString Duration;
	QString Lyric;
	QString LyricsTranslation;
	QByteArray Image;
};

enum class ETypeSort : int
{
	Unknown = 0,
	Alphabetical,
	Album,
	Artist,
	DateAdded
};

enum class EStateSort : int
{
	Unknown = 0,
	Ascending,
	Descending
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
	CantUseDatabase,
	CantCreateTable,
};

struct TypeResultQuery
{
public:
	TypeResultQuery(ETypeResultQuery t = ETypeResultQuery::Unknown) : m_result(t) {}

public:
	void operator=(ETypeResultQuery t)
	{
		this->m_result = t;
	}
	void operator=(TypeResultQuery t)
	{
		this->m_result = t.m_result;
	}
	int toInt()
	{
		return static_cast<int>(this->m_result);
	}
	operator int()
	{
		return static_cast<int>(this->m_result);
	}
	void SetValue(ETypeResultQuery t)
	{
		this->m_result = t;
	}
	friend bool operator==(const TypeResultQuery& left, const TypeResultQuery& right)
	{
		if (left.m_result == right.m_result)
		{
			return true;
		}
		return false;
	}
	friend bool operator==(const TypeResultQuery& left, const ETypeResultQuery right)
	{
		if (left.m_result == right)
		{
			return true;
		}
		return false;
	}
	friend bool operator==(const ETypeResultQuery left, const TypeResultQuery& right)
	{
		if (left == right.m_result)
		{
			return true;
		}
		return false;
	}
	friend bool operator==(const TypeResultQuery* const left, const ETypeResultQuery right)
	{
		if (left->m_result == right)
		{
			return true;
		}
		return false;
	}

private:
	ETypeResultQuery m_result;
};

class Database : protected QObject
{
	Q_OBJECT

public:
	Database(QObject* parent = Q_NULLPTR);
	~Database();

public:
	void Initialize();
	void CheckUser(const QByteArray& hash, TypeResultQuery* res);
	void CreateNewUser(const QByteArray& hash, TypeResultQuery* res);
	int UsersID(const QByteArray& hash);
	void Media(const QByteArray& hash, const int id, QByteArray* const buffer, TypeResultQuery* res);
	QJsonArray GetTable(const QByteArray& hash, ETypeTable type, const bool merger, const int limit, const int offset, const ETypeSort typeSort, const EStateSort stateSort, TypeResultQuery* res);
	void CoverArt(const QByteArray& hash, const int mediaID, QByteArray* const buffer, TypeResultQuery* res);
	void AddNewMedia(const QByteArray& hash, QByteArray* const buffer, const Tags& tags, bool newArtist, bool newAlbum, TypeResultQuery* res);

private:
	QSqlDatabase* m_pDatabase;
	QString m_path = QCoreApplication::applicationDirPath() + "/Data";
};

#endif
