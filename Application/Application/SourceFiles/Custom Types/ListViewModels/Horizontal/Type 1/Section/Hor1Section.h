#ifndef _SECTION_HOR_TYPE_1_H_
#define _SECTION_HOR_TYPE_1_H_

#include "StdAfx.h"

#include "Tools/Query.h"
#include "Interfaces/ISection.h"

#include "ListViewModels/Horizontal/Type 1/Model/Hor1Model.h"

namespace HorizontalModel1
{
	class Section : public ISection
	{
		Q_OBJECT

	public:
		Section(HorizontalModel1::List* m_listHorModel, ImageProvider* imageProvider);
		~Section();

	public:
		// ISection
		virtual void Initialize() override;
		// ~ISection

	public slots:
		void InitializeList();
		void UpdateImageItem(QByteArray data);
		void Load(QByteArray data);
		void Load(Table* table);

	signals:
		void onInitializeList();

	private:
		int m_current_item = 0;
		HorizontalModel1::List* m_listHorModel;
	};
}

#endif