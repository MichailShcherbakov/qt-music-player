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
	m_id = gParams->pSettings->value("MediaPlayer/id").toInt();
	m_title = gParams->pSettings->value("MediaPlayer/title").toString();
	m_artist = gParams->pSettings->value("MediaPlayer/artist").toString();
	m_time = gParams->pSettings->value("MediaPlayer/time").toString();

	connect(this, &FooterPanel::idChanged, this, [=]() {
		Query q;
		q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
		q.InsertIntoBody("id-media", m_id);
		q.InsertIntoBody("width", static_cast<int>(196));
		q.InsertIntoBody("height", static_cast<int>(196));
		emit sendToSocket(this, q.toByteArray());
	});
	connect(this, &FooterPanel::coverIDChanged, this, [=]() {
		gParams->pSettings->setValue("MediaPlayer/id", m_id);
	});
	connect(this, &FooterPanel::titleChanged, this, [=]() {
		gParams->pSettings->setValue("MediaPlayer/title", m_id);
	});
	connect(this, &FooterPanel::artistChanged, this, [=]() {
		gParams->pSettings->setValue("MediaPlayer/artist", m_id);
	});
	connect(this, &FooterPanel::timeChanged, this, [=]() {
		gParams->pSettings->setValue("MediaPlayer/time", m_id);
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
