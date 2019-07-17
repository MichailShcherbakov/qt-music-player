#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "StdAfx.h"

#include "Interfaces/IWindow.h"
#include "Screens/ListSongsScreen/ListSongsScreen.h"
#include "MediaPlayer/MediaPlayer.h"

class Player : public IWindow
{
	Q_OBJECT

enum class ETypeScreen : int
{
	Unknown = 0,
	ListSongs,
};

public:
	Player(const EParams* const params, QQuickWindow* window = Q_NULLPTR);
	~Player() override;

public:
	// IWindow
	virtual void Initialize() override;
	// ~IWindow

public slots:
	inline void MediaStatePlay() { emit mediaState(true); }
	inline void MediaStateStop() { emit mediaState(false); }

public:
	Q_INVOKABLE void next();
	Q_INVOKABLE void play();
	Q_INVOKABLE void previous();
	Q_INVOKABLE void clickedItem(int type, int id);

signals:
	// MediaPlayer
	void positionChanged(qint64 position);
	void durationChanged(qint64 duration);
	void currentTimeChanged(QString time);
	// ~MediaPlayer

	// ISection
	void changeTitleSong(QString title);
	void changeArtistSong(QString artist);
	void changeCoverArtSong(QString image);
	void changeTime(QString time);
	// ~ISection

signals:
	// QML
	void sliderPositionChanged(qint64 position);
	void playModeChanged(int state);
	void mediaChosen(int id);
	void mediaState(bool state);

private:
	ListSongsScreen* m_pListSongsScreen;
	MediaPlayer* m_pMediaPlayer;
	ETypeScreen m_typeScreen;
};

#endif
