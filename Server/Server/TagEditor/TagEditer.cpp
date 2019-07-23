#include "TagEditer.h"



CTagEditer::CTagEditer()
{
}


CTagEditer::~CTagEditer()
{
}

Tags CTagEditer::GetTags(QString path)
{
	TagLib::MPEG::File audio(path.toStdWString().c_str());
	TagLib::ID3v2::Tag* tag = audio.ID3v2Tag(true);

	Tags tags;
	tags.Album = QString::fromStdWString(tag->album().toCWString());
	tags.Artist = QString::fromStdWString(tag->artist().toCWString());
	tags.Genre = QString::fromStdWString(tag->genre().toCWString());
	tags.Title = QString::fromStdWString(tag->title().toCWString());
	tags.Year = QString::number(tag->year());
	tags.Bitrate = QString::number(audio.audioProperties()->bitrate());
	tags.Duraction = QString::number(audio.audioProperties()->lengthInSeconds());

	TagLib::ID3v2::FrameList listOfMp3Frames = tag->frameListMap()["APIC"];
	if (!listOfMp3Frames.isEmpty())
	{
		TagLib::ID3v2::FrameList::ConstIterator it = listOfMp3Frames.begin();
		for (; it != listOfMp3Frames.end(); it++)
		{
			TagLib::ID3v2::AttachedPictureFrame* pictureFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*> (*it);
			tags.Image = QByteArray(pictureFrame->picture().data(), pictureFrame->picture().size());
		}
	}

	return tags;
}

QByteArray CTagEditer::GetCoverArt(QString path)
{
	TagLib::MPEG::File audio(path.toStdWString().c_str());
	TagLib::ID3v2::Tag* tag = audio.ID3v2Tag(true);

	TagLib::ID3v2::FrameList listOfMp3Frames = tag->frameListMap()["APIC"];
	if (!listOfMp3Frames.isEmpty())
	{
		TagLib::ID3v2::FrameList::ConstIterator it = listOfMp3Frames.begin();
		for (; it != listOfMp3Frames.end(); it++)
		{
			TagLib::ID3v2::AttachedPictureFrame* pictureFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*> (*it);
			return QByteArray(pictureFrame->picture().data(), pictureFrame->picture().size());
		}
	}
	return QByteArray();
}
