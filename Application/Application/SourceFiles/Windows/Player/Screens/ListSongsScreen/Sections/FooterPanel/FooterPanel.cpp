#include "FooterPanel.h"

FooterPanel::FooterPanel(const EParams* const params) : 
	ISectionObject(params->m_pSocket),
	m_pParams(params)

{
	m_pParams->m_pRootContext->setContextProperty("FooterPanel", this);
}

FooterPanel::~FooterPanel()
{
}

void FooterPanel::Initialize()
{
	m_id = m_pParams->m_pSettings->value("MediaPlayer/id").toInt();
	m_title = m_pParams->m_pSettings->value("MediaPlayer/title").toString();
	m_artist = m_pParams->m_pSettings->value("MediaPlayer/artist").toString();
	m_time = m_pParams->m_pSettings->value("MediaPlayer/time").toString();

	connect(this, &FooterPanel::idChanged, this, [=]() {
		Query q;
		q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
		q.InsertIntoBody("id-media", m_id);
		emit onSendToSocket(this, q.toByteArray());
	});
	connect(this, &FooterPanel::coverIDChanged, this, [=]() {
		m_pParams->m_pSettings->setValue("MediaPlayer/id", m_id);
	});
	connect(this, &FooterPanel::titleChanged, this, [=]() {
		m_pParams->m_pSettings->setValue("MediaPlayer/title", m_id);
	});
	connect(this, &FooterPanel::artistChanged, this, [=]() {
		m_pParams->m_pSettings->setValue("MediaPlayer/artist", m_id);
	});
	connect(this, &FooterPanel::timeChanged, this, [=]() {
		m_pParams->m_pSettings->setValue("MediaPlayer/time", m_id);
	});
	connect(m_pParams->m_pMediaPlayer, &MediaPlayer::currentTimeChanged, this, [=](QString time) {
		m_currentTime = time;
		emit currentTimeChanged();
	});

	if (m_id != 0)
	{
		Query q;
		q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
		q.InsertIntoBody("id-media", m_id);
		emit onSendToSocket(this, q.toByteArray());
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

	m_coverID = QString::number(m_pParams->m_pRootImageProvider->SafeId());
	m_pParams->m_pRootImageProvider->AppendImage(p, m_coverID);

	emit coverIDChanged();
}
