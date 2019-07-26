#ifndef _CHAPTER_MEDIA_PLAYER_H_
#define _CHAPTER_MEDIA_PLAYER_H_

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

class ChapterMediaPlayer : public IÑhapter
{
	Q_OBJECT
	Q_PROPERTY(bool id MEMBER m_index NOTIFY indexChanged)
	Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged)
	Q_PROPERTY(QString artist MEMBER m_artist NOTIFY artistChanged)
	Q_PROPERTY(QString time MEMBER m_time NOTIFY timeChanged)
	Q_PROPERTY(PlayModeEnum::EPlayMode playMode MEMBER m_playMode NOTIFY playModeChanged)

public:
	ChapterMediaPlayer(QSettings* settings);
	~ChapterMediaPlayer() override;

public:
	void SetIndex(int index);
	int Index();

public:
	void SetTitle(QString title);
	QString Title();

public:
	void SetArtist(QString artist);
	QString Artist();

public:
	void SetTime(QString time);
	QString Time();

public:
	void SetPlayMode(PlayModeEnum::EPlayMode mode);
	PlayModeEnum::EPlayMode PlayMode();

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

private:
	int m_index = 0;
	QString m_title;
	QString m_artist;
	QString m_time;
	PlayModeEnum::EPlayMode m_playMode = PlayModeEnum::EPlayMode::Unknown;
};

#endif 