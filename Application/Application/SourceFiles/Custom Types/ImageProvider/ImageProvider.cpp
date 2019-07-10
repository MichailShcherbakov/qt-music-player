#include "ImageProvider/ImageProvider.h"



ImageProvider::ImageProvider()
	: QQuickImageProvider(QQuickImageProvider::Image)
{
}

ImageProvider::~ImageProvider()
{
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

	QStringList args = id.split('/');

	int res = args[0].remove(0, 1).toInt();

	if (m_list.find(args[1]) != m_list.end())
	{
		return m_list.value(args[1]).scaled(res, res, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}
	return QImage();
}

void ImageProvider::AppendImage(QImage image, QString id)
{
	m_list.insert(id, image);
	m_safeId++;
}

void ImageProvider::DeleteList()
{
	m_list.clear();
}

QImage ImageProvider::GetImage(QString id)
{
	if (m_list.find(id) != m_list.end())
	{
		return m_list.value(id);
	}
	return QImage();
}

QString ImageProvider::Find(QImage image)
{
	return m_list.key(image);
}

bool ImageProvider::Contains(QString id)
{
	return m_list.contains(id);
}

bool ImageProvider::Contains(QImage id)
{
	for (auto it : m_list)
	{
		if (it == id)
		{
			return true;
		}
	}
	return false;
}

void ImageProvider::Remove(QString id)
{
	m_list.remove(id);
}

int ImageProvider::SafeId()
{
	return m_safeId++;
}

int ImageProvider::Size()
{
	return m_list.size();
}
