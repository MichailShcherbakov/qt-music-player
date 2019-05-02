#include "CMediaData.h"



CMediaData::CMediaData()
{
}


CMediaData::~CMediaData()
{
}

void  CMediaData::GetMainData(QString path)
{
	TagLib::FileRef file(path.toStdWString().data());
	TagLib::Tag* tg = file.tag();

	m_title = QString::fromStdWString(tg->title().toWString());
	m_artist = QString::fromStdWString(tg->artist().toWString());
	m_genre = QString::fromStdWString(tg->genre().toWString());
	m_album = QString::fromStdWString(tg->album().toWString());
	m_year = QString::number(tg->year());

	file.save();
}

QByteArray CMediaData::GetImage(QString path)
{
	TagLib::MPEG::File mp3File(path.toStdWString().data());
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

void CMediaData::SetMetaData(QString path, Data list)
{
	TagLib::FileRef file(path.toStdWString().data());
	TagLib::Tag* tg = file.tag();

	tg->setTitle(list.title.toStdWString());
	tg->setArtist(list.artist.toStdWString());
	tg->setAlbum(list.album.toStdWString());
	tg->setGenre(list.genre.toStdWString());
	tg->setYear(list.year.toInt());

	file.save();
}

void CMediaData::SetImage(QString path, QByteArray* img)
{
	TagLib::MPEG::File audioFile("C:/Users/User/Desktop/b42e2a6d680e35.mp3");
	TagLib::MPEG::File image("C:/Users/User/Desktop/folder.jpg");

	TagLib::ID3v2::Tag* tag = audioFile.ID3v2Tag(true);
	TagLib::ID3v2::AttachedPictureFrame* frame = new TagLib::ID3v2::AttachedPictureFrame;

	

	//tag->setArtist("SHIT");

	//audioFile.save();

	frame->setMimeType("image/jpeg");
	frame->setPicture(image.readBlock(image.length()));
	tag->addFrame(frame);
	//frame->setPicture(img->data());

	audioFile.save();
}

QString CMediaData::GetTitle()
{
	return m_title;
}

QString CMediaData::GetArtist()
{
	return m_artist;
}

QString CMediaData::GetAlbum()
{
	return m_album;
}

QString CMediaData::GetGenre()
{
	return m_genre;
}

QString CMediaData::GetYear()
{
	return m_year;
}
