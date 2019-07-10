#ifndef _ILIST_H_
#define _ILIST_H_

#include "Tools/StdAfx.h"

#include <QObject>

struct IItem {};

class IList : public QObject
{
	Q_OBJECT

public:
	IList() {}
	virtual ~IList() {}

signals:
	void preItemAppended();
	void postItemAppended();

	void preItemInserted(int index);
	void postItemInserted();

	void preItemRemoved(int index);
	void postItemRemoved();
};

#endif