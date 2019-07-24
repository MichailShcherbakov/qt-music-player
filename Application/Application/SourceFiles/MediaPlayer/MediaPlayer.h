#ifndef _MEDIA_PLAYER_H_
#define _MEDIA_PLAYER_H_

#include <QMediaPlayer>
#include <QSettings>
#include <QBuffer>

#include "Interfaces/IMediaPlayer.h"
#include "Playlist/Playlist.h"

class MediaPlayer : public IMediaPlayer
{
	Q_OBJECT

public:
	MediaPlayer();
	~MediaPlayer() override;

public slots:
	// IMediaPlayer
	virtual void Initialize() override;
	virtual void ReadyRead(QByteArray package) override;
	virtual void GottenData(QByteArray data) override;
	virtual void Play(int id) override;
	virtual void Next() override;
	virtual void Previous() override;
	virtual void SetPlaylist(IPlaylist* const playlist) override;
	virtual int CurrentIndex() override;
	// ~IMediaPlayer

public:
	inline void SetPlayMode(int mode) { m_playMode = static_cast<EPlayMode>(mode); }

private:
	virtual void MediaStatusChanged(QMediaPlayer::MediaStatus status) override;
	virtual void ChangeCurrentTime(qint64 position) override;
	virtual void ChangeTime(qint64 position) override;

private:
	int oldSize = 0;
	int m_currentIndex = 0;
	QBuffer* m_pBuffer;
	Playlist* m_pPlaylist;
	QMediaPlayer* m_pPlayer;
	EPlayMode m_playMode;
	EPlayerState m_playState;
};

#endif
