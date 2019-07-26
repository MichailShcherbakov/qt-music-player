#include "StdAfx.h"
#include "FooterPanel.h"

FooterPanel::FooterPanel() : 
	ISectionObject(gParams->pSocket)
{
	gParams->pRootContext->setContextProperty("FooterPanel", this);
}

FooterPanel::~FooterPanel()
{
}

void FooterPanel::Initialize()
{
	m_id = gParams->pSettings->Chapters()->MediaPlayer()->Index();
	m_title = gParams->pSettings->Chapters()->MediaPlayer()->Title();
	m_artist = gParams->pSettings->Chapters()->MediaPlayer()->Artist();
	m_time = gParams->pSettings->Chapters()->MediaPlayer()->Time();

	connect(this, &FooterPanel::idChanged, this, [=]() {
		Query q;
		q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
		q.InsertIntoBody("id-media", m_id);
		q.InsertIntoBody("width", static_cast<int>(196));
		q.InsertIntoBody("height", static_cast<int>(196));
		emit sendToSocket(this, q.toByteArray());
	});
	connect(this, &FooterPanel::coverIDChanged, this, [=]() {
		gParams->pSettings->Chapters()->MediaPlayer()->SetIndex(m_id);
	});
	connect(this, &FooterPanel::titleChanged, this, [=]() {
		gParams->pSettings->Chapters()->MediaPlayer()->SetTitle(m_title);
	});
	connect(this, &FooterPanel::artistChanged, this, [=]() {
		gParams->pSettings->Chapters()->MediaPlayer()->SetArtist(m_artist);
	});
	connect(this, &FooterPanel::timeChanged, this, [=]() {
		gParams->pSettings->Chapters()->MediaPlayer()->SetTime(m_time);
	});
	connect(gParams->pMediaPlayer, &IMediaPlayer::currentTimeChanged, this, [=](QString time) {
		m_currentTime = time;
		emit currentTimeChanged();
	});

	if (m_id != 0)
	{
		Query q;
		q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
		q.InsertIntoBody("id-media", m_id);
		q.InsertIntoBody("width", static_cast<int>(196));
		q.InsertIntoBody("height", static_cast<int>(196));
		emit sendToSocket(this, q.toByteArray());
	}
}
void FooterPanel::ReadyRead(QByteArray package)
{
}

void FooterPanel::GottenData(QByteArray data)
{
	Query q;
	q.fromByteArray(data);

	QByteArray& image = q.GetFromBody("cover-art").toVariant().toString().toLatin1();

	QImage p;
	p.loadFromData(image, "JPG");

	m_coverID = gParams->pRootImageProvider->AppendImage(this, p);

	emit coverIDChanged();
}
