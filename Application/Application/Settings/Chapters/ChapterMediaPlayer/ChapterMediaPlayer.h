#ifndef _CHAPTER_MEDIA_PLAYER_H_
#define _CHAPTER_MEDIA_PLAYER_H_

#include "Interfaces/IChapterMediaPlayer.h"

class ChapterMediaPlayer : public IChapterMediaPlayer
{
	Q_OBJECT

public:
	ChapterMediaPlayer();
	~ChapterMediaPlayer() override;

public:
	virtual void SetIndex(int index) ;
	virtual int Index() override;

public:
	virtual void SetTitle(QString title) override;
	virtual QString Title() override;

public:
	virtual void SetArtist(QString artist) override;
	virtual QString Artist() override;

public:
	virtual void SetTime(QString time) override;
	virtual QString Time() override;

public:
	virtual void SetPlayMode(PlayModeEnum::EPlayMode mode) override;
	virtual PlayModeEnum::EPlayMode PlayMode() override;
};

#endif 