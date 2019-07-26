#ifndef _IMEDIAPLAYER_H_
#define _IMEDIAPLAYER_H_

#include <QObject>
#include <QMediaPlayer>

#include "Interfaces/ISection.h"
#include "Interfaces/IPlaylist.h"

class IMediaPlayer : public ISection
{
	Q_OBJECT

protected:
	enum class EPlayerState : int
	{
		Unknown = 0,
		Play,
		Pause,
	};

public:
	IMediaPlayer(Socket* socket)
		: ISection(socket)
	{
		connect(this, &INetwork::getFromSocket, this, &IMediaPlayer::ReadyRead);
		connect(this, &ISection::gottenData, this, &IMediaPlayer::GottenData);
	}
	virtual ~IMediaPlayer() {}

public slots:
	virtual void Initialize() = 0;
	virtual void ReadyRead(QByteArray package) = 0;
	virtual void GottenData(QByteArray data) = 0;
	virtual void Play(int id) = 0;
	virtual void Next() = 0;
	virtual void Previous() = 0;
	virtual void SetPlaylist(IPlaylist* const playlist) = 0;
	virtual int CurrentIndex() = 0;

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

protected:
	virtual void MediaStatusChanged(QMediaPlayer::MediaStatus status) = 0;
	virtual void ChangeCurrentTime(qint64 position) = 0;
};

#endif // !_CSOCKET_H_





