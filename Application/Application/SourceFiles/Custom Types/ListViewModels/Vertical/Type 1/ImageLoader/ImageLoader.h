#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

#include <QQueue>
#include <QThread>

#include "Interfaces/ISectionObject.h"
#include "ListViewModels/Vertical/Type 1/List/Ver1List.h"

namespace VerticalModel1
{
	class ImageLoader : public ISectionObject
	{
		Q_OBJECT

	public:
		ImageLoader(VerticalModel1::List* model, QHash<int, int>* listIndex, const QString title);
		~ImageLoader() override;

	public slots:
		// ISectionObject
		virtual void Initialize() override;
		virtual void ReadyRead(QByteArray package) override;
		virtual void GottenData(QByteArray data) override;
		// ~ISectionObject

	public slots:
		void LoadImageItem(int id);
		void DeleteImageItem(int id);
		void SetAvailable(bool available);
		void Clear();

	signals:
		void loadImageItem(int id);
		void deleteImageItem(int id);

	private:
		bool m_isAvailable = true;
		VerticalModel1::List* m_pModel;
		QHash<int, int>* m_pListIndex;
		QQueue<int> m_queueLoad;
		bool m_isQueueFree = true;
	};
}

#endif