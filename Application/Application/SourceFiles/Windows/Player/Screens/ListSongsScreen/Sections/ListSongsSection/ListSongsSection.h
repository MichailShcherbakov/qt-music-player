#ifndef _LIST_SONGS_SECTION_H_
#define _LIST_SONGS_SECTION_H_

#include "StdAfx.h"
#include "EParams.h"

#include "Interfaces/ISectionListView.h"

#include "ListViewModels/Vertical/Type 1/Model/Ver1Model.h"

#include "Interfaces/ISectionObject.h"
#include "Interfaces/ISection.h"

#include <QQueue>
#include <QThread>

class ImageManager : public ISectionObject
{
	Q_OBJECT

public:
	ImageManager(const EParams* const params, VerticalModel1::List* model, QHash<int, int>* listIndex) : 
		ISectionObject(params->m_pSocket),
		m_pParams(params),
		m_pListIndex(listIndex),
		m_pModel(model)
	{
		params->m_pRootContext->setContextProperty(QStringLiteral("imageManager"), this);
		connect(this, &ImageManager::onLoadImageItem, this, &ImageManager::LoadImageItem);
		connect(this, &ImageManager::onDeleteImageItem, this, &ImageManager::DeleteImageItem);
	}
	~ImageManager() {}

public slots:
	virtual void Initialize() override {}
	virtual void ReadyRead(QByteArray package) override {}
	virtual void GottenData(QByteArray data) override
	{
		if (m_isAvailable)
		{
			Query q;
			q.fromByteArray(data);

			QByteArray& image = q.GetFromBody("cover-art").toVariant().toString().toLatin1();

			QImage p;
			p.loadFromData(image, "JPG");

			QString id;

			if (p == QImage())
			{
				id = "default";
			}
			else if (m_pParams->m_pRootImageProvider->Contains(p))
			{
				id = m_pParams->m_pRootImageProvider->Find(p);
			}
			else
			{
				id = QString::number(m_pParams->m_pRootImageProvider->SafeId());
				m_pParams->m_pRootImageProvider->AppendImage(p, id);
			}

			if (!m_queueLoad.isEmpty())
			{
				int idImageModel = m_pListIndex->value(m_queueLoad.head());
				m_pModel->SetValueItemAt(idImageModel, id, VerticalModel1::List::COVER_KEY);

				m_queueLoad.dequeue();

			}

			m_isQueueFree = true;

			if (!m_queueLoad.isEmpty())
			{
				m_isQueueFree = false;

				Query q;
				q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
				q.InsertIntoBody("id-media", m_queueLoad.head());
				emit onSendToSocket(this, q.toByteArray());
			}
		}
	};

	void LoadImageItem(int id)
	{
		if (m_isAvailable)
		{
			m_queueLoad.enqueue(id);

			if (m_isQueueFree)
			{
				m_isQueueFree = false;

				Query q;
				q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
				q.InsertIntoBody("id-media", id);
				emit onSendToSocket(this, q.toByteArray());
			}
		}
	}
	void DeleteImageItem(int id)
	{
		if (m_isAvailable)
		{
			if (m_queueLoad.contains(id))
			{
				m_queueLoad.removeAt(m_queueLoad.indexOf(id));
			}

			int index = m_pListIndex->value(id);

			VerticalModel1::Item* t = &m_pModel->At(index);

			if (t->id == id)
			{
				m_pParams->m_pRootImageProvider->Remove(t->coverKey);
				m_pModel->SetValueItemAt(index, "default", VerticalModel1::List::COVER_KEY);
			}
		}
	}
	void SetAvailable(bool available)
	{
		m_isAvailable = available;
	}
	void Clear()
	{
		m_isQueueFree = true;
		m_isAvailable = true;
		m_queueLoad.clear();
		m_pListIndex->clear();
	}

signals:
	void onLoadImageItem(int id);
	void onDeleteImageItem(int id);

private:
	bool m_isAvailable = true;
	VerticalModel1::List* m_pModel;
	QHash<int, int>* m_pListIndex;
	QQueue<int> m_queueLoad;
	bool m_isQueueFree = true;
	const EParams* const m_pParams;
};

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
	virtual void SetCurrentItem(int item) override;
	// ~ISectionListView

public slots:
	void InitializeList();
	void LoadData();

signals:
	void initializeList();
	void clickedItem(int id);
	void hasClicked();

private:
	ImageManager* m_pImageManager;
	VerticalModel1::List* m_pModel;
	QList<ETypeLoad> m_requests;
	QHash<int, int> m_listIndex;
	bool m_isQueueFree = true;
	QThread* m_pThread;
	const EParams* const m_pParams;
};

#endif