#ifndef _IMAGE_PROVIDER_H_
#define _IMAGE_PROVIDER_H_

#include <QQuickImageProvider>

class ImageProvider : public QQuickImageProvider
{
public:
	ImageProvider();
	~ImageProvider();

public:
	QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
	void AppendImage(QImage image, QString id);
	void DeleteList();
	QImage GetImage(QString id);
	QString Find(QImage image);
	bool Contains(QString id);
	bool Contains(QImage id);
	void Remove(QString id);
	int SafeId();
	int Size();

private:
	unsigned long long m_safeId = 0;
	QMap<QString, QImage> m_list;
};

#endif

