#include "CMediaData.h"



CMediaData::CMediaData()
{
}


CMediaData::~CMediaData()
{
}

void  CMediaData::GetMainData(QString path)
{
	QByteArray media;

	TagLib::FileRef file(path.toUtf8().data());
	TagLib::Tag* tg = file.tag();

	m_title = QString::fromStdWString(tg->title().toWString());
	m_author = QString::fromStdWString(tg->artist().toWString());
	m_genre = QString::fromStdWString(tg->genre().toWString());
	m_year = QString::number(tg->year());

	file.save();
}

QByteArray CMediaData::GetImage(QString path)
{
	TagLib::MPEG::File mp3File(path.toUtf8().data());
	Tag * mp3Tag;
	FrameList listOfMp3Frames;
	AttachedPictureFrame * pictureFrame;
	QByteArray media;

	mp3Tag = mp3File.ID3v2Tag();
	if (mp3Tag)
	{
		listOfMp3Frames = mp3Tag->frameListMap()["APIC"];//look for picture frames only
		if (!listOfMp3Frames.isEmpty())
		{
			FrameList::ConstIterator it = listOfMp3Frames.begin();
			for (; it != listOfMp3Frames.end(); it++)
			{
				pictureFrame = static_cast<AttachedPictureFrame *> (*it);//cast Frame * to AttachedPictureFrame*

				//Warning. format of picture assumed to be jpg. This may be false, for example it may be png.
				//FILE * fout;
				//fopen_s(&fout, "C:\\Users\\User\\Desktop\\sonddg.jpg", "wb");
				media = QByteArray(reinterpret_cast<char*>(pictureFrame->picture().data()), pictureFrame->picture().size());
				//fwrite(pictureFrame->picture().data(), pictureFrame->picture().size(), 1, fout);
				//fclose(fout);
			}
		}
	}
	return media;
}

void CMediaData::SetMetaData(QString path, QVector<QString>* list)
{

}

void CMediaData::SetImage(QString path, QByteArray * img)
{

}

QString CMediaData::GetTitle()
{
	return m_title;
}

QString CMediaData::GetAuthor()
{
	return m_author;
}

QString CMediaData::GetGenre()
{
	return m_genre;
}

QString CMediaData::GetYear()
{
	return m_year;
}
