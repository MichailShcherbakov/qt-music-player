#include "StdAfx.h"
#include "ImageLoader.h"

VerticalModel1::ImageLoader::ImageLoader(VerticalModel1::List* model, QHash<int, int>* listIndex, const uint width, const uint height, const QString title) :
	ISectionObject(gParams->pSocket),
	m_pListIndex(listIndex),
	m_pModel(model),
	m_width(width),
	m_height(height)
{
	gParams->pRootContext->setContextProperty(title, this);
	connect(this, &ImageLoader::loadImageItem, this, &ImageLoader::LoadImageItem);
	connect(this, &ImageLoader::deleteImageItem, this, &ImageLoader::DeleteImageItem);
}

VerticalModel1::ImageLoader::~ImageLoader()
{
}

void VerticalModel1::ImageLoader::Initialize()
{
}

void VerticalModel1::ImageLoader::ReadyRead(QByteArray package)
{
}

void VerticalModel1::ImageLoader::GottenData(QByteArray data)
{
	Query q;
	q.fromByteArray(data);

	QByteArray& image = q.GetFromBody("cover-art").toVariant().toString().toLatin1();

	QImage p;
	p.loadFromData(image, "JPG");
	int w = p.width();

	QString id;

	if (p == QImage())
	{
		id = "default";
	}
	else
	{
		id = gParams->pRootImageProvider->AppendImage(this, p);
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
		q.InsertIntoBody("width", static_cast<int>(m_width));
		q.InsertIntoBody("height", static_cast<int>(m_height));
		emit sendToSocket(this, q.toByteArray());
	}
}

void VerticalModel1::ImageLoader::LoadImageItem(int id)
{
	MSG(ETypeMessage::Log, "Load image -> " + QString::number(id));

	m_queueLoad.enqueue(id);

	if (m_isQueueFree)
	{
		m_isQueueFree = false;

		Query q;
		q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
		q.InsertIntoBody("id-media", id);
		q.InsertIntoBody("width", static_cast<int>(m_width));
		q.InsertIntoBody("height", static_cast<int>(m_height));
		emit sendToSocket(this, q.toByteArray());
	}
}

void VerticalModel1::ImageLoader::DeleteImageItem(int id)
{
	MSG(ETypeMessage::Log, "Delete image -> " + QString::number(id));

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
			gParams->pRootImageProvider->Remove(this, t->coverKey);
			m_pModel->SetValueItemAt(index, "default", VerticalModel1::List::COVER_KEY);
		}
	}
}

void VerticalModel1::ImageLoader::SetAvailable(bool available)
{
	m_isAvailable = available;
}

void VerticalModel1::ImageLoader::Clear()
{
	m_isQueueFree = true;
	m_isAvailable = true;
	m_queueLoad.clear();
	m_pListIndex->clear();
}