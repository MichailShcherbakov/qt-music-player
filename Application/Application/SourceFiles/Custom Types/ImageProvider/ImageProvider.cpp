#include "StdAfx.h"
#include "ImageProvider.h"

ImageProvider::ImageProvider()
	: QQuickImageProvider(QQuickImageProvider::Image)
{
	QFile img("Resources/Icons/cover.jpg");
	img.open(QIODevice::ReadOnly);
	QByteArray arrayImg = img.readAll();
	img.close();

	m_defaultImage.loadFromData(arrayImg, "JPG");
	m_defaultImage = m_defaultImage.scaled(10, 10, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

ImageProvider::~ImageProvider()
{
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
	QStringList args = id.split('/');

	int res = args[0].remove(0, 1).toInt();

	if (args[1] == "default")
	{
		return m_defaultImage;
	}

	if (m_list.find(args[1]) != m_list.end())
	{
		return m_list.value(args[1])->second;
	}

	return QImage();
}

QString ImageProvider::AppendImage(QObject* const object, QImage image)
{
	for (auto it : m_list)
	{
		if (it->second == image)
		{
			it->first.append(object);
			return m_list.key(it);
		}
	}

	m_safeId++;

	QList<QObject*> t;
	t.append(object);
	m_list.insert(QString::number(m_safeId), new QPair<QList<QObject*>, QImage>(t, image));
	return QString::number(m_safeId);
}

void ImageProvider::Clear()
{
	m_list.clear();
}

QImage ImageProvider::GetImage(QString id)
{
	if (m_list.find(id) != m_list.end())
	{
		return m_list.value(id)->second;
	}
	return QImage();
}

QList<QString> ImageProvider::GetId(QObject* const object)
{
	QList<QString> t;

	for (auto it : m_list)
	{
		if (it->first.contains(object))
		{
			t.append(m_list.key(it));
		}
	}
	return t;
}

QString ImageProvider::Find(const QImage& image)
{
	for (auto it : m_list)
	{
		if (it->second == image)
		{
			return m_list.key(it);
		}
	}
	return QString();
}

bool ImageProvider::Contains(QString id)
{
	return m_list.contains(id);
}

bool ImageProvider::Contains(QImage image)
{
	for (auto it : m_list)
	{
		if (it->second == image)
		{
			return true;
		}
	}
	return false;
}

void ImageProvider::Remove(QObject* const object, QString id)
{
	if (m_list.contains(id))
	{
		auto item = m_list.value(id);

		if (item->first.contains(object))
		{
			item->first.removeOne(object);
		}

		if (item->first.isEmpty())
		{
			m_list.remove(id);
			delete item;
		}
	}
}

int ImageProvider::Size()
{
	return m_list.size();
}
