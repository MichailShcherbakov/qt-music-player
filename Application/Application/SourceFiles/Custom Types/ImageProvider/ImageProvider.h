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
	int Size();

private:
	QMap<QString, QImage> m_list;
};

#endif

