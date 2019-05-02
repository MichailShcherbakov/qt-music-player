#ifndef _CIMAGEPROVIDER_H_
#define _CIMAGEPROVIDER_H_

#include <QQuickImageProvider>

class CImageProvider : public QQuickImageProvider
{
public:
	CImageProvider();
	~CImageProvider();

public:
	QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
	void AppendImage(QImage image, QString id);
	void DeleteList();
	QImage GetImage(QString id);

private:
	QMap<QString, QImage> m_list;
};

#endif

