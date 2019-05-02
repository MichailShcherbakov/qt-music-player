#ifndef _CMEDIA_DATA_H_
#define _CMEDIA_DATA_H_

#include <QVector>
#include <QString>

/*taglib specific includes*/
#include <fileref.h>
#include <tbytevector.h>			//ByteVector
#include <mpegfile.h>				//mp3 file
#include <id3v2tag.h>				//tag
#include <id3v2frame.h>				//frame
#include <attachedPictureFrame.h>	//attachedPictureFrame

using namespace TagLib::ID3v2;

struct Data
{
	QString title;
	QString artist;
	QString album;
	QString genre;
	QString year;
};


class CMediaData
{
public:
	CMediaData();
	~CMediaData();

public:
	void GetMainData(QString path);
	QByteArray GetImage(QString path);

public:
	void SetMetaData(QString path, Data list);
	void SetImage(QString path, QByteArray* img);

public:
	QString GetTitle();
	QString GetArtist();
	QString GetAlbum();
	QString GetGenre();
	QString GetYear();

private:
	QString m_title;
	QString m_artist;
	QString m_album;
	QString m_genre;
	QString m_year;
};

#endif
