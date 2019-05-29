#ifndef _C_TagEditer_H_
#define _C_TagEditer_H_

#include <QString>
#include <QFile>
#include <QTextStream>

/*taglib specific includes*/
#include <taglib/tag.h>
#include <fileref.h>
#include <tbytevector.h>			//ByteVector
#include <mpegfile.h>				//mp3 file
#include <id3v2tag.h>				//tag
#include <id3v2frame.h>				//frame
#include <attachedPictureFrame.h>	//attachedPictureFrame

#pragma comment(lib, "tag.lib")

struct Tags
{
	QString Title;
	QString Artist;
	QString Album;
	QString Genre;
	QString Year;
	QString Bitrate;
	QString Duraction;
	QByteArray Image;
};

class CTagEditer
{
public:
	CTagEditer();
	~CTagEditer();

public:
	Tags GetTags(QString path);
	QByteArray GetCoverArt(QString path);
};

#endif

