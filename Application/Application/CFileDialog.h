#ifndef _CFILEDIALOG_H_
#define _CFILEDIALOG_H_

#include "StdAfx.h"

#include "IDialog.h"

#include "CImageProvider.h"
#include "CList.h"
#include "CTagEditer.h"
#include "CTable.h"

#include <QFile>

class CFileDialog : public IDialog
{
	Q_OBJECT

public:
	CFileDialog(QQuickWindow* window, CList* list, CImageProvider* provider);
	virtual ~CFileDialog();

public:
	// IWindow
	virtual void Initialize() override;
	// ~IWindow

public:
	Q_INVOKABLE void getFiles(QList<QUrl> urls);
	Q_INVOKABLE void onClickedItem(QString fileName);
	Q_INVOKABLE void onRemoveItem(QString fileName);
	Q_INVOKABLE void saveImage(QString path);
	Q_INVOKABLE void finish();
	Q_INVOKABLE void saveFeatures(QString title, QString artist, QString album, QString genre, QString year);

signals:
	void setTitle(QString title);
	void setArtist(QString artist);
	void setAlbum(QString album);
	void setGenre(QString genre);
	void setYear(QString year);
	void setImage(QString image);

private:
	void isClickedColor();

private:
	int temp_count;
	int m_currentSelectedItem;
	QMap<QString, QString> m_urls;
	CList* m_list;
	CImageProvider* m_imageProvider;
};

#endif
