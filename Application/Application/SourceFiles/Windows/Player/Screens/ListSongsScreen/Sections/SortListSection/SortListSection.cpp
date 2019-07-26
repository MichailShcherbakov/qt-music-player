#include "StdAfx.h"
#include "SortListSection.h"

SortListSection::SortListSection() : 
	ISectionObject(gParams->pSocket)
{
	gParams->pRootContext->setContextProperty(QStringLiteral("sortListSection"), this);
}

SortListSection::~SortListSection()
{
}

void SortListSection::Initialize()
{
	connect(this, &SortListSection::update, this, &SortListSection::Update);
	connect(this, &SortListSection::setType, this, &SortListSection::SetType);
	connect(this, &SortListSection::setState, this, &SortListSection::SetState);
}

void SortListSection::ReadyRead(QByteArray package)
{
}

void SortListSection::GottenData(QByteArray data)
{
}

void SortListSection::SetType(int type)
{
	gParams->pSettings->setValue("SortTables/sortType", type);
	
	emit sortChanged();
}

void SortListSection::SetState(int state)
{
	gParams->pSettings->setValue("SortTables/sortState", state);

	emit sortChanged();
}

void SortListSection::Update()
{
	gParams->pSettings->beginGroup("SortTables");
	int type = gParams->pSettings->value("sortType").toInt();
	int state = gParams->pSettings->value("sortState").toInt();
	gParams->pSettings->endGroup();

	emit setCheckType(type);
	emit setCheckState(state);
}


