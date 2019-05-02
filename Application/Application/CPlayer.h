#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "StdAfx.h"

#include "IWindow.h"

#include <QObject>
#include <QFile>
#include <QString>
#include <QBuffer>
#include <QDir>
#include <QMediaPlayer>

#include "CImageProvider.h"
#include "CMediaData.h"
#include "CTable.h"
#include "CList.h"



class CPlayer : public IWindow
{
	Q_OBJECT

public:
	explicit CPlayer(QQuickWindow* window, CQuery* query, CList* list, CImageProvider* imageProvider);
	virtual ~CPlayer();

private:
	enum class EStateNetwork : int
	{
		WAITING = -1,
		INITIALIZE_ALL_MUSIC,
		GETTING_NEEDED_MUSIC,
		GETTING_NEEDED_IMAGE,
		SENDING_NEW_MUSIC,
	};
	enum class EStatePlayer : int
	{
		Pause = 0,
		Play,
	};
	enum class EPlayMode : int
	{
		SEQUENTIAL = 0,
		LOOP,
		CURRENT_ITEM_IN_LOOP,
	};

public:
	// IWindow
	virtual void Initialize() override;
	virtual void getFromSocket(QByteArray* data) override;
	// ~IWindow

public:
	Q_INVOKABLE void button_play();
	Q_INVOKABLE void button_next();
	Q_INVOKABLE void button_back();
	Q_INVOKABLE void button_local_files();
	Q_INVOKABLE void positionChanging(qint64 pos);
	Q_INVOKABLE void list_view(QString name, QString title);

signals:
	void changeImagePlayButton(QString path);
	void changeImageCover(QString media);
	void positionChanged(qint64 pos);
	void mediaChanged(qint64 size);

public slots:
	void MediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
	void PlayMedia();

private:
	CTable* m_table;
	CList* m_list;
	QBuffer* m_buffer;
	QMediaPlayer* m_player;
	int m_current_media_loadding;
	int m_current_media;
	EStatePlayer m_statePlayer = EStatePlayer::Pause;
	EStateNetwork m_stateNetwork = EStateNetwork::WAITING;
	EPlayMode m_playMode = EPlayMode::SEQUENTIAL;
	CImageProvider* m_imageProvider;
	

};

#endif // CPLAYER_H