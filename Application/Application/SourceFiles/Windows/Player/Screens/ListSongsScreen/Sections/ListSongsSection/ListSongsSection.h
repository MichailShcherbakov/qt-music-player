#ifndef _LIST_SONGS_SECTION_H_
#define _LIST_SONGS_SECTION_H_

#include "StdAfx.h"

#include "Interfaces/ISectionListView.h"

#include "ListViewModels/Vertical/Type 1/Model/Ver1Model.h"

class ListSongsSection : public ISectionListView
{
	Q_OBJECT

public:
	ListSongsSection(const EParams* const params);
	~ListSongsSection() override;

public slots:
	// ISectionListView
	virtual void Initialize() override;
	virtual void ReadyRead(QByteArray package) override;
	virtual void GottenData(QByteArray data) override;
	virtual void ClickedItem(int id) override;
	virtual void FirstIndex() override;
	virtual void EndIndex() override;
	virtual void NextIndex(int id) override;
	virtual void PreviousIndex(int id) override;
	// ~ISectionListView

public slots:
	void InitializeList();
	void UpdateImageItem(QByteArray image);
	void LoadImageItem(int id);
	void DeleteImageItem(int id);

signals:
	void onInitializeList();
	void onChangeTime(QString time);
	void onChangeTitleSong(QString title);
	void onChangeArtistSong(QString artist);
	void onChangeCoverArtSong(QString image);
	void onLoadImageItem(int id);
	void onDeleteImageItem(int id);

private:
	int m_current_item = 0;
	VerticalModel1::List* m_model;
	QList<ETypeLoad> m_requests;
	QList<int> m_idLoadImage;
	QHash<int, int> m_listIndex;
	bool m_isQueueFree = true;
};

#endif