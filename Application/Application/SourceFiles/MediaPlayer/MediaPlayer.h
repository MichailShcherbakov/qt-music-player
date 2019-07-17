#ifndef _MEDIA_PLAYER_H_
#define _MEDIA_PLAYER_H_

#include "StdAfx.h"

#include <QMediaPlayer>
#include <QBuffer>

#include "Interfaces/ISection.h"
#include "Interfaces/ISectionListView.h"

class MediaPlayer : public ISection
{
	Q_OBJECT

public:
	MediaPlayer(const EParams* const paramas);
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
	inline void SetPosition(qint64 position) { m_pPlayer.setPosition(position); }
	inline void SetPlayMode(int mode) { m_playMode = static_cast<EPlayMode>(mode); }
	inline int CurrentID() { return m_currentID; }
	void SetConnnectWithSection(ISectionListView* section);
	void GetID(int id);

signals:
	void onPositionChanged(qint64 position);
	void onDurationChanged(qint64 duration);
	void onCurrentTimeChanged(QString time);
	void onStarted(int id);
	void onPaused(int id);
	void onGetNextIndex(int id);
	void onGetEndIndex(int id);
	void onGetFirstIndex(int id);
	void onGetPreviousIndex(int id);

private:
	void MediaStatusChanged(QMediaPlayer::MediaStatus status);
	void ChangeCurrentTime(qint64 position);

private:
	int m_currentID = 0;
	QBuffer* m_pBuffer;
	QMediaPlayer m_pPlayer;
	EPlayMode m_playMode;
	EPlayerState m_playState;
	ISectionListView* m_pHandleSection;
};

#endif
