#ifndef _SORT_LIST_SECTION_H_
#define _SORT_LIST_SECTION_H_

#include "Interfaces/ISectionObject.h"

class SortListSection : public ISectionObject
{
	Q_OBJECT

public:
	SortListSection();
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
	void update();
	void setType(int type);
	void setState(int state);
	void setCheckType(int type);
	void setCheckState(int state);
	void sortChanged();
};

#endif