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
	gParams->pSettings->Chapters()->SortTables()->SetType(static_cast<SortTypeEnum::ESortType>(type));
	
	emit sortChanged();
}

void SortListSection::SetState(int state)
{
	gParams->pSettings->Chapters()->SortTables()->SetState(static_cast<SortStateEnum::ESortState>(state));

	emit sortChanged();
}

void SortListSection::Update()
{
	int type = static_cast<int>(gParams->pSettings->Chapters()->SortTables()->Type());
	int state = static_cast<int>(gParams->pSettings->Chapters()->SortTables()->State());

	emit setCheckType(type);
	emit setCheckState(state);
}


