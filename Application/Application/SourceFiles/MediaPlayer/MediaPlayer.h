#ifndef _MEDIA_PLAYER_H_
#define _MEDIA_PLAYER_H_

#include <QMediaPlayer>
#include <QSettings>
#include <QBuffer>

#include "Interfaces/IMediaPlayer.h"
#include "Interfaces/IPlaylist.h"

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

private:
	virtual void MediaStatusChanged(QMediaPlayer::MediaStatus status) override;
	virtual void ChangeCurrentTime(qint64 position) override;

private:
	int m_oldSizeBuffer = 0;
	int m_currentIndex = 0;
	QBuffer* m_pBuffer;
	IPlaylist* m_pPlaylist;
	QMediaPlayer* m_pPlayer;
	PlayModeEnum::EPlayMode m_playMode;
	EPlayerState m_playState;
};

#endif
