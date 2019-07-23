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

private:
	ListSongsScreen* m_pListSongsScreen;
	ETypeScreen m_typeScreen;
};

#endif
