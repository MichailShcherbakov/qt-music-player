#ifndef _SORT_LIST_SECTION_H_
#define _SORT_LIST_SECTION_H_

#include "StdAfx.h"
#include "EParams.h"

#include "Interfaces/ISectionObject.h"

class SortListSection : public ISectionObject
{
	Q_OBJECT

public:
	SortListSection(const EParams* const params);
	~SortListSection() override;

public slots:
	// ISection
	virtual void Initialize() override;
	virtual void ReadyRead(QByteArray package) override;
	virtual void GottenData(QByteArray data) override;
	// ~ISection

public slots:
	void Update();
	void SetType(int type);
	void SetState(int state);

signals:
	void onUpdate();
	void onSetType(int type);
	void onSetState(int state);
	void setCheckType(int type);
	void setCheckState(int state);
	void onSortChanged();

private:
	const EParams* const m_pParams;
};

#endif