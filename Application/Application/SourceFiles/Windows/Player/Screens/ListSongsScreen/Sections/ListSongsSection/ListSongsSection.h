#ifndef _LIST_SONGS_SECTION_H_
#define _LIST_SONGS_SECTION_H_

#include "Interfaces/ISectionListView.h"

#include "ListViewModels/Vertical/Type 1/Model/Ver1Model.h"
#include "ListViewModels/Vertical/Type 1/ImageLoader/ImageLoader.h"

class ListSongsSection : public ISectionListView
{
	Q_OBJECT

public:
	ListSongsSection();
	~ListSongsSection() override;

public slots:
	// ISectionListView
	virtual void Initialize() override;
	virtual void ReadyRead(QByteArray package) override;
	virtual void GottenData(QByteArray data) override;
	virtual void ClickedItem(int id) override;
	virtual void SetCurrentItem(int item) override;
	// ~ISectionListView

public slots:
	void InitializeList();
	void LoadData();
	void GetMediaMergedTable(Query& data);

signals:
	void initializeList();
	void clickedItem(int id);
	void clicked();

private:
	VerticalModel1::ImageLoader* m_pImageManager;
	VerticalModel1::List* m_pModel;
	QHash<int, int> m_listIndex;
	QThread* m_pThread;
	Table* m_pTable;
};

#endif