#include "CImageProvider.h"



CImageProvider::CImageProvider()
	: QQuickImageProvider(QQuickImageProvider::Image)
{
}

CImageProvider::~CImageProvider()
{
}

QImage CImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

	QStringList args = id.split('/');

	int res = args[0].remove(0, 1).toInt();

	if (m_list.find(args[1]) != m_list.end())
	{
		return m_list.value(args[1]).scaled(res, res, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}
}

void CImageProvider::AppendImage(QImage image, QString id)
{
	m_list.insert(id, image);
}

void CImageProvider::DeleteList()
{
	m_list.clear();
}

QImage CImageProvider::GetImage(QString id)
{
	if (m_list.find(id) != m_list.end())
	{
		return m_list.value(id);
	}
}
