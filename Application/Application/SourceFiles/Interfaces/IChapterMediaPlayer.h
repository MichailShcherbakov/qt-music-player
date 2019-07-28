#ifndef _ICHAPTER_MEDIA_PLAYER_H_
#define _ICHAPTER_MEDIA_PLAYER_H_

#include "Interfaces/IChapter.h"

struct PlayModeEnum
{
	Q_GADGET

public:
	explicit PlayModeEnum();

	enum class EPlayMode : uint
	{
		Unknown = 0,
		Sequential,
		Loop,
		CurrentItemInLoop,
	};

	Q_ENUM(EPlayMode)
};

class IChapterMediaPlayer : public IÑhapter
{
	Q_OBJECT
	Q_PROPERTY(int id MEMBER m_index NOTIFY indexChanged)
	Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged)
	Q_PROPERTY(QString artist MEMBER m_artist NOTIFY artistChanged)
	Q_PROPERTY(QString time MEMBER m_time NOTIFY timeChanged)
	Q_PROPERTY(PlayModeEnum::EPlayMode playMode MEMBER m_playMode NOTIFY playModeChanged)

public:
	IChapterMediaPlayer() {}
	virtual ~IChapterMediaPlayer() {}

public:
	virtual void SetIndex(int index) = 0;
	virtual int Index() = 0;

public:
	virtual void SetTitle(QString title) = 0;
	virtual QString Title() = 0;

public:
	virtual void SetArtist(QString artist) = 0;
	virtual QString Artist() = 0;

public:
	virtual void SetTime(QString time) = 0;
	virtual QString Time() = 0;

public:
	virtual void SetPlayMode(PlayModeEnum::EPlayMode mode) = 0;
	virtual PlayModeEnum::EPlayMode PlayMode() = 0;

signals:
	void indexChanged();
	void titleChanged();
	void artistChanged();
	void timeChanged();
	void playModeChanged();

signals:
	void changeIndex();
	void changeTitle();
	void changeArtist();
	void changeTime();
	void changePlayMode();

protected:
	int m_index = 0;
	QString m_title;
	QString m_artist;
	QString m_time;
	PlayModeEnum::EPlayMode m_playMode = PlayModeEnum::EPlayMode::Unknown;
};

#endif 