#ifndef _IMAGE_PROVIDER_H_
#define _IMAGE_PROVIDER_H_

#include <QFile>
#include <QQuickImageProvider>

class ImageProvider : public QQuickImageProvider
{
public:
	ImageProvider();
	~ImageProvider();

public:
	QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
	QString AppendImage(QObject* const object, QImage image);
	void Clear();
	QImage GetImage(QString id);
	QList<QString> GetId(QObject* const object);
	QString Find(const QImage& image);
	bool Contains(QString id);
	bool Contains(QImage image);
	void Remove(QObject* const object, QString id);
	int Size();

private:
	unsigned long long m_safeId = 0;
	QHash<QString, QPair<QList<QObject*>, QImage>*> m_list;
	QImage m_defaultImage;
};

#endif

