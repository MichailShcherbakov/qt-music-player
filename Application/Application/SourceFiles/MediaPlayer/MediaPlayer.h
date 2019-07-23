#ifndef _MEDIA_PLAYER_H_
#define _MEDIA_PLAYER_H_

#include "StdAfx.h"

#include <QMediaPlayer>
#include <QSettings>
#include <QBuffer>

#include "Interfaces/ISection.h"
#include "Interfaces/ISectionObject.h"
#include "Interfaces/ISectionListView.h"

class MediaPlayer : public ISectionObject
{
	Q_OBJECT

public:
	MediaPlayer(Socket* const socket, QQmlContext* const context, QSettings* const settings);
	~MediaPlayer();

public:
	enum class EPlayerState : int
	{
		Unknown = 0,
		Play,
		Stop,
	};

	enum class EPlayMode : int
	{
		Unknown = 0,
		Sequential,
		Loop,
		Current_item_in_loop,
	};

public:
	// ISection
	virtual void Initialize() override;
	virtual void ReadyRead(QByteArray package) override;
	virtual void GottenData(QByteArray data) override;
	// ~ISection

public slots:
	void PlayTheSong(int id);
	void Next();
	void Previous();
	inline void SetPlayMode(int mode) { m_playMode = static_cast<EPlayMode>(mode); }
	inline int CurrentID() { return m_currentID; }
	void SetConnnectWithSection(ISectionListView* section);
	void GetID(int id);
	inline ISectionListView* GetSection() { return m_pHandleSection; }

signals:
	void positionChanged(int position);
	void durationChanged(int duration);
	void setPosition(int position);
	void currentTimeChanged(QString time);
	void next();
	void previous();
	void play();
	void pause();
	void started(int id);
	void paused(int id);
	void getNextIndex(int id);
	void getEndIndex(int id);
	void getFirstIndex(int id);
	void getPreviousIndex(int id);

private:
	void MediaStatusChanged(QMediaPlayer::MediaStatus status);
	void ChangeCurrentTime(qint64 position);
	void ChangeTime(qint64 position);

private:
	int oldSize = 0;
	int m_currentID = 0;
	QBuffer* m_pBuffer;
	QMediaPlayer* m_pPlayer;
	EPlayMode m_playMode;
	EPlayerState m_playState;
	ISectionListView* m_pHandleSection;
	Socket* const m_pSocket;
	QQmlContext* const m_pRootContext;
	QSettings* const m_pSettings;
};

#endif
