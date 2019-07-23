#include "SortListSection.h"

SortListSection::SortListSection(const EParams* const params) : 
	ISectionObject(params->m_pSocket),
	m_pParams(params)
{
	params->m_pRootContext->setContextProperty(QStringLiteral("sortListSection"), this);
}

SortListSection::~SortListSection()
{
}

void SortListSection::Initialize()
{
	connect(this, &SortListSection::onUpdate, this, &SortListSection::Update);
	connect(this, &SortListSection::onSetType, this, &SortListSection::SetType);
	connect(this, &SortListSection::onSetState, this, &SortListSection::SetState);
}

void SortListSection::ReadyRead(QByteArray package)
{
}

void SortListSection::GottenData(QByteArray data)
{
}

void SortListSection::SetType(int type)
{
	m_pParams->m_pSettings->beginGroup("SortTables");
	m_pParams->m_pSettings->setValue("sortType", type);
	m_pParams->m_pSettings->endGroup();
	
	emit onSortChanged();
}

void SortListSection::SetState(int state)
{
	m_pParams->m_pSettings->beginGroup("SortTables");
	m_pParams->m_pSettings->setValue("sortState", state);
	m_pParams->m_pSettings->endGroup();

	emit onSortChanged();
}

void SortListSection::Update()
{
	m_pParams->m_pSettings->beginGroup("SortTables");
	int type = m_pParams->m_pSettings->value("sortType").toInt();
	int state = m_pParams->m_pSettings->value("sortState").toInt();
	m_pParams->m_pSettings->endGroup();

	emit setCheckType(type);
	emit setCheckState(state);
}


