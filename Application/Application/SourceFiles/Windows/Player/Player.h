#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Interfaces/IWindow.h"

#include "Screens/ListSongsScreen/ListSongsScreen.h"

class Player : public IWindow
{
	Q_OBJECT

enum class ETypeScreen : int
{
	Unknown = 0,
	ListSongs,
};

public:
	Player(QQuickWindow* window = Q_NULLPTR);
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
