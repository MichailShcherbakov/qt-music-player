#include "CTagEditer.h"



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

	return tags;
}
